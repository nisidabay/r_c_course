/*
 * Exercise 07 — SQLite3 Database
 *
 * Create a SQLite3 database, create a table, insert a row, and query it.
 *
 * Expected output:
 *   Name: Alice, Score: 95
 *
 * Hints:
 *   - sqlite3 *db; sqlite3_open("test.db", &db);
 *   - sqlite3_exec(db, "CREATE TABLE ...", ...);
 *   - Use prepared statements for INSERT and SELECT
 *   - sqlite3_step() to iterate results
 *   - sqlite3_close(db); remove("test.db");
 *   - Compile with -lsqlite3
 *   - #include <sqlite3.h>, <stdio.h>, <stdlib.h>
 */
