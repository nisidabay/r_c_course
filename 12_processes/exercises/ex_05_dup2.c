/*
 * Exercise 05 — dup2 Redirect
 *
 * Use dup2 to redirect stdout to a file, then restore it.
 *
 * Expected output:
 *   This goes to the terminal.
 *   (a file "output.txt" is created with "This goes to the file.")
 *
 * Hints:
 *   - int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
 *   - int saved = dup(STDOUT_FILENO);  // save original
 *   - dup2(fd, STDOUT_FILENO);         // redirect
 *   - printf("This goes to the file.\n");
 *   - dup2(saved, STDOUT_FILENO);      // restore
 *   - close(fd); close(saved); remove("output.txt");
 *   - #include <unistd.h>, <fcntl.h>, <stdio.h>, <stdlib.h>
 */
