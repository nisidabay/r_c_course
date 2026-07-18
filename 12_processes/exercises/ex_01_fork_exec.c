/*
 * Exercise 01 — fork + exec (launch uname)
 *
 * Fork a child process and use exec to run the "uname -a" command.
 *
 * Expected output (will vary by system):
 *   Parent PID: 12345, Child PID: 12346
 *   [output of uname -a]
 *
 * Hints:
 *   - pid_t pid = fork();
 *   - if (pid == 0) { execlp("uname", "uname", "-a", NULL); perror("execlp"); _exit(1); }
 *   - else { wait(NULL); printf("Child finished\n"); }
 *   - #include <unistd.h>, <sys/wait.h>, <stdio.h>, <stdlib.h>
 */
