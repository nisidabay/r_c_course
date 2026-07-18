/*
 * journal.c — A personal journal in C (Group 12 capstone)
 *
 * Uses ALL concepts from groups 01-12:
 *   - fork+exec+waitpid (concept 01): launch the user's editor
 *   - execlp/execvp     (concept 02): runtime program resolution
 *   - getenv            (concept 06): read $EDITOR, $HOME
 *   - getopt_long       (concept 08): parse --db, --help flags
 *   - mkdir             (concept 08): create ~/.journal/ on first run
 *   - snprintf          (group 04):   build file paths
 *   - getopt_mkdir      (concept 08): parse flags and create directory
 *   - sqlite3           (concept 07): persistent storage
 *   - fgets + truncation   (group 01):   read user input
 *   - EXIT_SUCCESS/     (group 03):   standard exit codes
 *     EXIT_FAILURE
 *   - perror            (group 09):   error reporting
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic journal.c -o journal -lsqlite3
 * Run:    ./journal new
 *         ./journal list
 *         ./journal edit 1
 *         ./journal --help
 */

#define _POSIX_C_SOURCE 200809L
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sqlite3.h>

/* ---- Database helpers ---- */

static sqlite3 *db_open(const char *path)
{
    sqlite3 *db;
    int rc = sqlite3_open(path, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
    return db;
}

static int db_exec(sqlite3 *db, const char *sql)
{
    char *err = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return -1;
    }
    return 0;
}

/* ---- Path helpers ---- */

static int ensure_dir(const char *path)
{
    if (mkdir(path, 0755) == 0)
        return 0;
    if (access(path, F_OK) == 0)
        return 0;   /* already exists — that's fine */
    perror("mkdir");
    return -1;
}

/* ---- Actions ---- */

static int cmd_new(sqlite3 *db, const char *editor)
{
    /* Create a temp file for the editor */
    const char *tmpdir = getenv("TMPDIR");
    if (!tmpdir) tmpdir = "/tmp";

    char tmpfile[512];
    int n = snprintf(tmpfile, sizeof tmpfile, "%s/journal_entry_XXXXXX", tmpdir);
    if (n < 0 || (size_t)n >= sizeof tmpfile) {
        fprintf(stderr, "Temp path too long\n");
        return EXIT_FAILURE;
    }

    /* mkstemp creates and opens a unique temp file */
    int fd = mkstemp(tmpfile);
    if (fd < 0) {
        perror("mkstemp");
        return EXIT_FAILURE;
    }
    close(fd);

    /* Launch the editor on the temp file */
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        unlink(tmpfile);
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        execlp(editor, editor, tmpfile, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    waitpid(pid, NULL, 0);

    /* Read the temp file back */
    FILE *fp = fopen(tmpfile, "r");
    if (!fp) {
        perror("fopen");
        unlink(tmpfile);
        return EXIT_FAILURE;
    }

    /* Read the entire file into memory */
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    if (fsize <= 0) {
        printf("Empty entry — not saved.\n");
        fclose(fp);
        unlink(tmpfile);
        return EXIT_SUCCESS;
    }

    char *content = malloc((size_t)fsize + 1);
    if (!content) {
        perror("malloc");
        fclose(fp);
        unlink(tmpfile);
        return EXIT_FAILURE;
    }

    size_t bytes_read = fread(content, 1, (size_t)fsize, fp);
    content[bytes_read] = '\0';
    fclose(fp);
    unlink(tmpfile);

    /* Escape single quotes for SQL */
    char *escaped = sqlite3_mprintf("%q", content);
    free(content);

    /* Save to database */
    char sql[8192];
    n = snprintf(sql, sizeof sql,
                "INSERT INTO entries (content, created_at) VALUES "
                "('%s', datetime('now'));", escaped);
    sqlite3_free(escaped);

    if (n < 0 || (size_t)n >= sizeof sql) {
        fprintf(stderr, "Entry too long\n");
        return EXIT_FAILURE;
    }

    if (db_exec(db, sql) != 0)
        return EXIT_FAILURE;

    printf("Entry saved (id: %lld)\n", sqlite3_last_insert_rowid(db));
    return EXIT_SUCCESS;
}

static int cmd_list(sqlite3 *db)
{
    const char *query = "SELECT id, content, created_at FROM entries "
                        "ORDER BY id DESC LIMIT 20;";

    char **result;
    char *err;
    int rows, cols;

    int rc = sqlite3_get_table(db, query, &result, &rows, &cols, &err);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return EXIT_FAILURE;
    }

    if (rows == 0) {
        printf("No entries yet.  Use '%s new' to create one.\n", "journal");
        sqlite3_free_table(result);
        return EXIT_SUCCESS;
    }

    for (int r = 1; r <= rows; r++) {
        const char *id_str = result[r * cols + 0];
        char *endptr;
        errno = 0;
        long id_long = strtol(id_str, &endptr, 10);
        int id;
        if (errno == ERANGE || endptr == id_str || *endptr != '\0'
            || id_long < INT_MIN || id_long > INT_MAX) {
            fprintf(stderr, "Error: invalid ID in database: %s\n", id_str);
            sqlite3_free_table(result);
            return EXIT_FAILURE;
        }
        id = (int)id_long;
        const char *content  = result[r * cols + 1];
        const char *date     = result[r * cols + 2];

        /* Print first 60 chars of content as a preview */
        char preview[64];
        int n = snprintf(preview, sizeof preview, "%s", content);
        if (n < 0) preview[0] = '\0';
        if ((size_t)n >= sizeof preview)
            snprintf(preview + sizeof preview - 4, 4, "...");

        /* Collapse newlines in preview */
        for (char *p = preview; *p; p++)
            if (*p == '\n') *p = ' ';

        printf("%3d  %s  %s\n", id, date, preview);
    }

    sqlite3_free_table(result);
    return EXIT_SUCCESS;
}

static int cmd_edit(sqlite3 *db, int entry_id, const char *editor)
{
    /* Fetch the entry content */
    char sql[256];
    int n = snprintf(sql, sizeof sql,
                    "SELECT content FROM entries WHERE id = %d;", entry_id);
    if (n < 0 || (size_t)n >= sizeof sql) {
        fprintf(stderr, "SQL too long\n");
        return EXIT_FAILURE;
    }

    char **result;
    char *err;
    int rows, cols;

    int rc = sqlite3_get_table(db, sql, &result, &rows, &cols, &err);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return EXIT_FAILURE;
    }

    if (rows == 0) {
        printf("Entry %d not found.\n", entry_id);
        sqlite3_free_table(result);
        return EXIT_FAILURE;
    }

    const char *content = result[cols + 1];  /* skip header row */

    /* Write content to a temp file */
    const char *tmpdir = getenv("TMPDIR");
    if (!tmpdir) tmpdir = "/tmp";

    char tmpfile[512];
    n = snprintf(tmpfile, sizeof tmpfile, "%s/journal_edit_XXXXXX", tmpdir);
    if (n < 0 || (size_t)n >= sizeof tmpfile) {
        fprintf(stderr, "Temp path too long\n");
        sqlite3_free_table(result);
        return EXIT_FAILURE;
    }

    int fd = mkstemp(tmpfile);
    if (fd < 0) {
        perror("mkstemp");
        sqlite3_free_table(result);
        return EXIT_FAILURE;
    }

    /* Write the content */
    write(fd, content, strlen(content));
    close(fd);

    /* Launch editor */
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        unlink(tmpfile);
        sqlite3_free_table(result);
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        execlp(editor, editor, tmpfile, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    waitpid(pid, NULL, 0);

    /* Read back */
    FILE *fp = fopen(tmpfile, "r");
    if (!fp) {
        perror("fopen");
        unlink(tmpfile);
        sqlite3_free_table(result);
        return EXIT_FAILURE;
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    char *new_content = NULL;
    if (fsize > 0) {
        new_content = malloc((size_t)fsize + 1);
        if (new_content) {
            size_t br = fread(new_content, 1, (size_t)fsize, fp);
            new_content[br] = '\0';
        }
    }
    fclose(fp);
    unlink(tmpfile);

    /* Update database */
    if (new_content && new_content[0] != '\0') {
        char *escaped = sqlite3_mprintf("%q", new_content);
        free(new_content);

        n = snprintf(sql, sizeof sql,
                    "UPDATE entries SET content = '%s' WHERE id = %d;",
                    escaped, entry_id);
        sqlite3_free(escaped);

        if (n < 0 || (size_t)n >= sizeof sql) {
            fprintf(stderr, "Entry too long\n");
            sqlite3_free_table(result);
            return EXIT_FAILURE;
        }

        if (db_exec(db, sql) != 0) {
            sqlite3_free_table(result);
            return EXIT_FAILURE;
        }
        printf("Entry %d updated.\n", entry_id);
    } else {
        printf("No changes — entry %d kept as-is.\n", entry_id);
    }

    sqlite3_free_table(result);
    return EXIT_SUCCESS;
}

/* ---- Main ---- */

int main(int argc, char *argv[])
{
    /* Default config */
    const char *db_path = NULL;

    static struct option long_options[] = {
        {"db",   required_argument, NULL, 'd'},
        {"help", no_argument,       NULL, 'h'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "d:h", long_options, NULL)) != -1) {
        switch (opt) {
        case 'd':
            db_path = optarg;
            break;
        case 'h':
            printf("Usage: %s <command> [args]\n", argv[0]);
            printf("\nCommands:\n");
            printf("  new          Create a new journal entry\n");
            printf("  list         Show recent entries\n");
            printf("  edit <id>    Edit an existing entry\n");
            printf("\nOptions:\n");
            printf("  --db PATH    Use custom database path\n");
            printf("  --help       Show this help\n");
            return EXIT_SUCCESS;
        default:
            fprintf(stderr, "Try '%s --help' for usage.\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s <command> [args]\n", argv[0]);
        fprintf(stderr, "Try '%s --help' for details.\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Read environment */
    const char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "$HOME not set\n");
        return EXIT_FAILURE;
    }

    const char *editor = getenv("EDITOR");
    if (!editor) editor = "vi";

    /* Ensure config directory */
    char config_dir[512];
    int n = snprintf(config_dir, sizeof config_dir, "%s/.journal", home);
    if (n < 0 || (size_t)n >= sizeof config_dir) {
        fprintf(stderr, "Path too long\n");
        return EXIT_FAILURE;
    }

    if (ensure_dir(config_dir) != 0)
        return EXIT_FAILURE;

    /* Resolve database path */
    char default_db[512];
    if (!db_path) {
        n = snprintf(default_db, sizeof default_db,
                    "%s/journal.db", config_dir);
        if (n < 0 || (size_t)n >= sizeof default_db) {
            fprintf(stderr, "Database path too long\n");
            return EXIT_FAILURE;
        }
        db_path = default_db;
    }

    /* Open database */
    sqlite3 *db = db_open(db_path);
    if (!db)
        return EXIT_FAILURE;

    /* Ensure schema */
    const char *schema = "CREATE TABLE IF NOT EXISTS entries ("
                         "  id         INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "  content    TEXT NOT NULL,"
                         "  created_at TEXT NOT NULL"
                         ");";
    if (db_exec(db, schema) != 0) {
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    /* Dispatch command */
    const char *cmd = argv[optind];
    int result = EXIT_SUCCESS;

    if (strcmp(cmd, "new") == 0) {
        result = cmd_new(db, editor);
    } else if (strcmp(cmd, "list") == 0) {
        result = cmd_list(db);
    } else if (strcmp(cmd, "edit") == 0) {
        if (optind + 1 >= argc) {
            fprintf(stderr, "Usage: %s edit <id>\n", argv[0]);
            result = EXIT_FAILURE;
        } else {
            const char *id_str = argv[optind + 1];
            char *endptr;
            errno = 0;
            long id_long = strtol(id_str, &endptr, 10);
            int entry_id;
            if (errno == ERANGE || endptr == id_str || *endptr != '\0'
                || id_long < INT_MIN || id_long > INT_MAX) {
                fprintf(stderr, "Error: invalid entry ID: %s\n", id_str);
                result = EXIT_FAILURE;
            } else {
                entry_id = (int)id_long;
                result = cmd_edit(db, entry_id, editor);
            }
        }
    } else {
        fprintf(stderr, "Unknown command: %s\n", cmd);
        fprintf(stderr, "Try '%s --help' for usage.\n", argv[0]);
        result = EXIT_FAILURE;
    }

    sqlite3_close(db);
    return result;
}
