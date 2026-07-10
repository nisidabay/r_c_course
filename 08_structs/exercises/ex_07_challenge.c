/*
 * Challenge: Student Grade Record System
 *
 * Build a small system that manages student records using struct arrays.
 * The program should:
 *   1. Define a Student struct with name, id, and 3 test scores
 *   2. Ask the user how many students to enter (max 10)
 *   3. For each student, read name, id, and 3 test scores
 *   4. Calculate and store the average for each student
 *   5. Display a formatted table of all students with their grades
 *
 * Constraints:
 *   - Use fgets + sscanf for ALL input (NO scanf/atoi/atof)
 *   - Use snprintf for string copy (NO strcpy)
 *   - int main(void)
 *   - Compiles with -std=c11
 *   - Student names max 63 chars + null terminator
 *
 * Example output:
 *   How many students? 2
 *
 *   Student 1:
 *   Name: Alice
 *   ID: 101
 *   Scores (3): 85 90 92
 *
 *   Student 2:
 *   Name: Bob
 *   ID: 102
 *   Scores (3): 78 82 88
 *
 *   --- Grade Report ---
 *   #   Name       ID    Score1  Score2  Score3  Average
 *   1   Alice      101   85      90      92      89.0
 *   2   Bob        102   78      82      88      82.7
 */

#include <stdio.h>

#define MAX_STUDENTS 10
#define MAX_NAME     64
#define NUM_SCORES   3

/* TODO: Define a Student struct with:
 *   - char name[MAX_NAME]
 *   - int id
 *   - int scores[NUM_SCORES]
 *   - double average
 */


int main(void) {
    char buf[64];
    int count = 0;

    printf("How many students? ");
    if (fgets(buf, sizeof buf, stdin) == NULL)
        return 1;
    if (sscanf(buf, "%d", &count) != 1 || count < 1 || count > MAX_STUDENTS) {
        printf("Invalid count (1-%d).\n", MAX_STUDENTS);
        return 1;
    }

    /* TODO: Declare an array of Student structs of size 'count' */

    /* TODO: Loop to read data for each student
     *   For each student:
     *     - Print "Student N:"
     *     - Prompt for name, read with fgets, strip newline
     *     - Prompt for id, read with fgets+sscanf
     *     - Prompt for 3 scores, read with fgets+sscanf
     *     - Calculate average: (score1 + score2 + score3) / 3.0
     */

    /* TODO: Display the grade report table
     *   Header: "--- Grade Report ---"
     *   Then:    "#   Name       ID    Score1  Score2  Score3  Average"
     *   For each student, print formatted row
     */

    return 0;
}
