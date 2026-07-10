/* sysinfo — print system info (hostname, user, OS) */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    char hostname[256];
    const char *user = getenv("USER");
    if (user == NULL) {
        user = "unknown";
    }

    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("gethostname");
        return EXIT_FAILURE;
    }
    hostname[sizeof(hostname) - 1] = '\0';

    printf("Host: %s\n", hostname);
    printf("User: %s\n", user);
    printf("OS:   Linux\n");

    return EXIT_SUCCESS;
}
