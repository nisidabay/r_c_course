/*
 * How do I check a child's exit status?
 *
 * waitpid() fills a status integer.  WIFEXITED tells us the child
 * terminated normally, WEXITSTATUS extracts its exit code.
 * WIFSIGNALED tells us the child was killed by a signal,
 * and WTERMSIG gives the signal number.
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
        printf("Child (PID %d) will exit with code 7.\n", (int)getpid());
        _exit(7);
    }

    int status;
    pid_t waited = waitpid(pid, &status, 0);

    if (waited < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    if (WIFEXITED(status)) {
        printf("Child exited normally with status %d.\n",
               WEXITSTATUS(status));
    }

    if (WIFSIGNALED(status)) {
        printf("Child was killed by signal %d.\n",
               WTERMSIG(status));
    }

    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// Every process returns an exit code. 0 is success, non-zero is error. The shell checks this.
