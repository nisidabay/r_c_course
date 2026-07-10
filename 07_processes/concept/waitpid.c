/*
 * How do I wait for a child to finish?
 *
 * waitpid() suspends the caller until the specified child terminates.
 * WIFEXITED and WEXITSTATUS macros let us inspect the exit status.
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
        printf("Child (PID %d) exiting with code 42.\n", (int)getpid());
        _exit(42);
    }

    int status;
    pid_t waited = waitpid(pid, &status, 0);

    if (waited < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    if (WIFEXITED(status)) {
        printf("Child exited with status %d.\n", WEXITSTATUS(status));
    }

    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// waitpid blocks until a child finishes. WIFEXITED and WEXITSTATUS decode the exit status.
