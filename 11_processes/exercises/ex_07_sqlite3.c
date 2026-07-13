/*
 * Exercise 07 — sqlite3: database operations
 * Concept reference: 07_sqlite3.c
 *
 * Task: Write a program that:
 *   1. Opens (or creates) an SQLite database called "notes.db".
 *   2. Creates a table called "topics" with columns:
 *        id    INTEGER PRIMARY KEY AUTOINCREMENT
 *        name  TEXT NOT NULL
 *   3. Inserts a row: name = 'processes'
 *   4. Queries all rows from the topics table and prints each name.
 *
 * Required calls:
 *   - sqlite3_open()         (taught in 07_sqlite3.c)
 *   - sqlite3_exec()         (taught in 07_sqlite3.c)
 *   - sqlite3_get_table()    (taught in 07_sqlite3.c)
 *   - sqlite3_free_table()   (taught in 07_sqlite3.c)
 *   - sqlite3_close()        (taught in 07_sqlite3.c)
 *   - sqlite3_errmsg()       (taught in 07_sqlite3.c)
 *   - EXIT_SUCCESS / EXIT_FAILURE
 *
 * Required includes:
 *   #include <sqlite3.h>
 *   #include <stdio.h>
 *   #include <stdlib.h>
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic ex_07_sqlite3.c -o ex_07_sqlite3 -lsqlite3
 *
 * Hints:
 *   - sqlite3_open("notes.db", &db) returns SQLITE_OK on success.
 *   - sqlite3_exec(db, sql, NULL, NULL, &err) returns SQLITE_OK on success.
 *   - Always free err with sqlite3_free(err) after a failed sqlite3_exec.
 *   - Use "CREATE TABLE IF NOT EXISTS" to avoid errors on re-runs.
 *   - For the query:
 *       char **result;
 *       int rows, cols;
 *       sqlite3_get_table(db, "SELECT name FROM topics", &result, &rows, &cols, &err);
 *       // result[0] = column name, result[1..rows] = data
 *       for (int r = 1; r <= rows; r++)
 *           printf("%s\n", result[r * cols + 0]);
 *       sqlite3_free_table(result);
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(void)
{
    sqlite3 *db = NULL;
    char *err = NULL;

    /* TODO: open database */
    // sqlite3_open("notes.db", &db)

    /* TODO: create topics table */
    // sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS ...", NULL, NULL, &err)

    /* TODO: insert a row */
    // sqlite3_exec(db, "INSERT INTO topics ...", NULL, NULL, &err)

    /* TODO: query all rows with sqlite3_get_table and print each name */
    // sqlite3_get_table(db, "SELECT name FROM ...", &result, &rows, &cols, &err)
    // for (int r = 1; r <= rows; r++) printf("%s\n", result[r * cols + 0]);
    // sqlite3_free_table(result)

    /* TODO: close database */
    // sqlite3_close(db);

    /* Stub: placeholder so this compiles */
    fprintf(stderr, "Exercise stub — implement sqlite3 operations\n");
    return EXIT_FAILURE;
}
