/*
 * Exercise 08 — Challenge: Journal Entry
 *
 * Write a program that reads a journal entry from stdin and appends it
 * to a SQLite3 database with a timestamp.
 *
 * Expected interaction:
 *   Enter your journal entry: Today I learned C!
 *   Entry saved.
 *
 * Then query the database to show all entries.
 *
 * Hints:
 *   - SQLite3 database with CREATE TABLE IF NOT EXISTS
 *   - fgets to read the entry
 *   - Get current time with time(NULL), format with ctime() or strftime()
 *   - INSERT with prepared statement, then SELECT to display
 *   - Compile with -lsqlite3
 *   - #include <sqlite3.h>, <time.h>, <string.h>, <errno.h>, <stdio.h>, <stdlib.h>
 */
