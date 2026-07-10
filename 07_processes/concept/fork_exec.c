/*
 * How do I create a child process?
 *
 * fork() creates a new process by duplicating the calling process.
 * The child gets return value 0; the parent gets the child's PID.
 * getpid() returns the PID of the calling process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        printf("Child process:  PID = %d, Parent PID = %d\n",
               (int)getpid(), (int)getppid());
    } else {
        printf("Parent process: PID = %d, Child PID = %d\n",
               (int)getpid(), (int)pid);
        wait(NULL);
    }

    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// fork creates a child process. exec replaces the child with a new program. fork returns 0 in the child.
