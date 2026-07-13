/*
 * Exercise 07 — sqlite3: database operations — SOLUTION
 * Concept reference: 07_sqlite3.c
 *
 * Opens notes.db, creates a topics table, inserts a row, queries it
 * using sqlite3_get_table() — the same approach taught in concept 07.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(void)
{
    sqlite3 *db = NULL;
    char *err = NULL;

    /* ---- Open database ---- */
    if (sqlite3_open("notes.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return EXIT_FAILURE;
    }

    /* ---- Create topics table ---- */
    const char *sql_create = "CREATE TABLE IF NOT EXISTS topics ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                             "name TEXT NOT NULL)";

    if (sqlite3_exec(db, sql_create, NULL, NULL, &err) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    /* ---- Insert a row ---- */
    const char *sql_insert = "INSERT INTO topics(name) VALUES('processes')";

    if (sqlite3_exec(db, sql_insert, NULL, NULL, &err) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    /* ---- Query all rows with get_table (like concept 07) ---- */
    char **result;
    int rows, cols;

    if (sqlite3_get_table(db, "SELECT name FROM topics",
                          &result, &rows, &cols, &err) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    for (int r = 1; r <= rows; r++) {
        printf("%s\n", result[r * cols + 0]);
    }

    sqlite3_free_table(result);

    /* ---- Close database ---- */
    sqlite3_close(db);

    return EXIT_SUCCESS;
}
