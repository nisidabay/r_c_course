/*
 * How do I run a command and read its output?
 *
 * popen("command", "r") spawns a shell process and returns a FILE *
 * connected to its stdout.  pclose() waits for the process to finish.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    FILE *fp = popen("echo hello from popen", "r");
    if (fp == NULL) {
        perror("popen");
        return EXIT_FAILURE;
    }

    char buf[256];
    if (fgets(buf, (int)sizeof(buf), fp) != NULL) {
        printf("Command output: %s", buf);
    }

    int ret = pclose(fp);
    if (ret == -1) {
        perror("pclose");
        return EXIT_FAILURE;
    }

    printf("Command exit status: %d\n", WEXITSTATUS(ret));

    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// popen runs a command and gives you a FILE star to read its output. Always close the pipe.
