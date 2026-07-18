/*
 * 08_getopt_mkdir.c — How do I parse CLI flags and create config directories?
 *
 * A real program needs two things to be useful:
 *   1. Command-line flags (--db, --help) so the user can configure it
 *   2. A place to store its data ($HOME/.myapp/)
 *
 * getopt_long() parses both short (-d) and long (--db) options.
 * mkdir() creates a directory.  Both are POSIX standards.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    /* ---- Parse command-line flags with getopt_long ---- */

    /* Default values */
    const char *db_path = NULL;
    int         verbose = 0;

    /* Define the long options we accept */
    static struct option long_options[] = {
        {"db",      required_argument, NULL, 'd'},
        {"verbose", no_argument,       NULL, 'v'},
        {"help",    no_argument,       NULL, 'h'},
        {0, 0, 0, 0}   /* sentinel — marks end of array */
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "d:vh", long_options, NULL)) != -1) {
        switch (opt) {
        case 'd':
            db_path = optarg;
            break;
        case 'v':
            verbose = 1;
            break;
        case 'h':
            printf("Usage: %s [--db PATH] [--verbose] [--help]\n", argv[0]);
            printf("  -d, --db PATH    Database file path\n");
            printf("  -v, --verbose    Print extra information\n");
            printf("  -h, --help       Show this help\n");
            return EXIT_SUCCESS;
        default:
            fprintf(stderr, "Try '%s --help' for usage.\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    /* ---- Create config directory ---- */
    const char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "HOME not set\n");
        return EXIT_FAILURE;
    }

    char config_dir[512];
    int n = snprintf(config_dir, sizeof config_dir,
                    "%s/.config/journal-app", home);
    if (n < 0 || (size_t)n >= sizeof config_dir) {
        fprintf(stderr, "Config path too long\n");
        return EXIT_FAILURE;
    }

    /* mkdir(path, mode) creates the directory.  0755 = rwxr-xr-x */
    if (mkdir(config_dir, 0755) == 0) {
        printf("[OK] Created directory: %s\n", config_dir);
    } else if (access(config_dir, F_OK) == 0) {
        printf("[OK] Directory already exists: %s\n", config_dir);
    } else {
        perror("mkdir");
        fprintf(stderr, "Could not create %s\n", config_dir);
        return EXIT_FAILURE;
    }

    /* ---- Resolve database path ---- */
    char resolved_db[512];

    if (!db_path) {
        n = snprintf(resolved_db, sizeof resolved_db,
                    "%s/journal.db", config_dir);
        if (n < 0 || (size_t)n >= sizeof resolved_db) {
            fprintf(stderr, "Database path too long\n");
            return EXIT_FAILURE;
        }
        db_path = resolved_db;
    }

    printf("Database: %s\n", db_path);

    if (verbose) {
        printf("\nConfiguration summary:\n");
        printf("  Home directory:  %s\n", home);
        printf("  Config dir:      %s\n", config_dir);
        printf("  Database:        %s\n", db_path);
        printf("  Verbose mode:    on\n");
    }

    return EXIT_SUCCESS;
}

// Thinking in C:
// getopt_long + getenv + mkdir is the holy trinity of portable C
// programs.  Parse flags, read the user's environment, create your
// data directory.  Every real CLI tool does this — from git to curl
// to neovim itself.

/*
 * 🚫 optarg as global — why we copy it
 * getopt_long sets optarg to point INSIDE argv.  If your program
 * later modifies argv or calls getopt_long again, the pointer becomes
 * invalid.  Always copy optarg to your own buffer or use it immediately.
 */
