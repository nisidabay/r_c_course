/*
 * 07_sqlite3.c — How do I store persistent data from C?
 *
 * SQLite is the most widely deployed database engine — it's embedded
 * directly in your program, no server, no setup.  Just three function
 * calls let your C program store and retrieve structured data.
 *
 * Compile with:  gcc -std=c11 -Wall -Wextra -pedantic 07_sqlite3.c -o demo -lsqlite3
 *
 * NOTE: You need the sqlite3 development library installed.
 *   Arch:  sudo pacman -S sqlite3
 *   Debian:sudo apt install libsqlite3-dev
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int main(void)
{
    sqlite3 *db = NULL;
    char    *err = NULL;
    int      rc;

    puts("=== sqlite3: embedded database from C ===\n");

    /* ---- Open (or create) a database ---- */
    rc = sqlite3_open("/tmp/demo.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return EXIT_FAILURE;
    }
    puts("[OK] Database opened /tmp/demo.db\n");

    /* ---- Create a table ---- */
    const char *create = "CREATE TABLE IF NOT EXISTS entries ("
                         "  id    INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "  title TEXT NOT NULL,"
                         "  words INTEGER NOT NULL"
                         ");";

    rc = sqlite3_exec(db, create, NULL, NULL, &err);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        sqlite3_close(db);
        return EXIT_FAILURE;
    }
    puts("[OK] Table 'entries' ready\n");

    /* ---- Insert rows ---- */
    const char *insert = "INSERT INTO entries (title, words) VALUES "
                         "  ('First entry', 142),"
                         "  ('Shopping list', 28),"
                         "  ('Project notes', 89);";

    rc = sqlite3_exec(db, insert, NULL, NULL, &err);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        sqlite3_close(db);
        return EXIT_FAILURE;
    }
    printf("[OK] Inserted %d rows\n\n", sqlite3_changes(db));

    /* ---- Query rows ---- */
    printf("Entries in the database:\n");
    printf("  ID  | Title          | Words\n");
    printf("  ----+----------------+------\n");

    const char *query = "SELECT id, title, words FROM entries ORDER BY id;";

    rc = sqlite3_exec(db, query, NULL, NULL, &err);
    /* We'll use a simpler callback-free approach */
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    /*
     * sqlite3_exec with a callback prints each row.  For simplicity
     * here we use sqlite3_get_table instead for batch queries:
     */
    {
        char **result;
        int    rows, cols;

        rc = sqlite3_get_table(db, query, &result, &rows, &cols, &err);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err);
            sqlite3_free(err);
            sqlite3_close(db);
            return EXIT_FAILURE;
        }

        /* result[0..cols-1] = column names, result[cols..] = data */
        for (int r = 1; r <= rows; r++) {
            printf("  %-4s | %-14s | %s\n",
                   result[r * cols + 0],
                   result[r * cols + 1],
                   result[r * cols + 2]);
        }

        sqlite3_free_table(result);
    }

    /* ---- Close ---- */
    sqlite3_close(db);
    puts("\n[OK] Database closed");

    return EXIT_SUCCESS;
}

// Thinking in C:
// sqlite3 gives your C program persistent storage with three calls:
// sqlite3_open, sqlite3_exec, sqlite3_close.  No server, no config,
// no dependencies beyond -lsqlite3 at compile time.  This is how
// real C programs (Firefox, Chrome, Dropbox) store data.

/*
 * 🚫 sqlite3_exec callback — why we use get_table instead
 * sqlite3_exec() can take a callback function that's called for each
 * row.  But callbacks split your logic across two functions and make
 * error handling harder.  sqlite3_get_table() returns ALL results at
 * once in a flat array — simpler for beginners.  Use the callback
 * form when you process millions of rows and need streaming.
 */
