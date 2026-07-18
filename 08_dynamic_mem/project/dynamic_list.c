/**
 * dynamic_list.c — Dynamic Contact List
 *
 * A simple contact manager demonstrating dynamic memory allocation
 * with a growable array of Contact structs.
 *
 * Concepts: malloc, realloc, free, NULL-checking, snprintf, fgets+strtol
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic dynamic_list.c -o dynamic_list
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── Helper: drain stdin residue after truncated fgets ──────────── */

static void consume_remaining(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* ── Structs ────────────────────────────────────────────────────────── */

typedef struct {
    char name[64];
    char phone[16];
} Contact;

typedef struct {
    Contact *contacts;
    size_t   len;
    size_t   cap;
} ContactList;

/* ── Functions ──────────────────────────────────────────────────────── */

/**
 * contactlist_create — initialise a ContactList with zero capacity
 */
void contactlist_create(ContactList *list)
{
    list->contacts = NULL;
    list->len      = 0;
    list->cap      = 0;
}

/**
 * contactlist_add — append a Contact; grow the backing array when full
 *
 * Uses realloc with a temp pointer so that a failure does not leak
 * the original buffer.
 */
int contactlist_add(ContactList *list, Contact c)
{
    if (list->len == list->cap) {
        size_t new_cap = list->cap == 0 ? 4 : list->cap * 2;
        Contact *tmp = realloc(list->contacts, new_cap * sizeof(Contact));
        if (tmp == NULL) {
            fprintf(stderr, "Error: memory reallocation failed\n");
            return -1;
        }
        list->contacts = tmp;
        list->cap      = new_cap;
    }

    list->contacts[list->len] = c;
    list->len++;
    return 0;
}

/**
 * contactlist_print — display every contact in the list
 */
void contactlist_print(const ContactList *list)
{
    if (list->len == 0) {
        printf("Contact list is empty.\n");
        return;
    }

    printf("\n── Contact List ──────────────────────\n");
    for (size_t i = 0; i < list->len; i++) {
        char display[128];
        snprintf(display, sizeof display, "%zu. %-20s  %s",
                 i + 1, list->contacts[i].name, list->contacts[i].phone);
        printf("%s\n", display);
    }
    printf("──────────────────────────────────────\n");
}

/**
 * contactlist_free — release all dynamically allocated memory
 */
void contactlist_free(ContactList *list)
{
    free(list->contacts);
    list->contacts = NULL;
    list->len      = 0;
    list->cap      = 0;
}

/* ── Main ───────────────────────────────────────────────────────────── */

int main(void)
{
    ContactList list;
    contactlist_create(&list);

    char line[128];

    printf("Dynamic Contact List\n");
    printf("────────────────────\n");
    printf("Enter a name and phone, or:\n");
    printf("  'p' — print all contacts\n");
    printf("  'q' — quit\n\n");

    while (1) {
        printf(">> ");

        if (fgets(line, sizeof line, stdin) == NULL) {
            /* EOF — treat as quit */
            break;
        }

        size_t len = strlen(line);
        if (len > 0 && line[len - 1] != '\n') {
            consume_remaining();
        } else if (len > 0) {
            line[len - 1] = '\0';
        }

        /* Empty input — re-prompt */
        if (line[0] == '\0')
            continue;

        /* Commands */
        if (line[0] == 'q' && line[1] == '\0') {
            break;
        }
        if (line[0] == 'p' && line[1] == '\0') {
            contactlist_print(&list);
            continue;
        }

        /* Otherwise expect "name,phone" — parse manually */
        Contact c;
        char *comma = strchr(line, ',');
        if (comma != NULL) {
            size_t name_len = comma - line;
            if (name_len >= sizeof c.name) name_len = sizeof c.name - 1;
            memcpy(c.name, line, name_len);
            c.name[name_len] = '\0';

            const char *phone_str = comma + 1;
            /* Trim leading spaces from phone */
            while (*phone_str == ' ') phone_str++;
            snprintf(c.phone, sizeof c.phone, "%s", phone_str);

            if (contactlist_add(&list, c) != 0) {
                fprintf(stderr, "Failed to add contact.\n");
            } else {
                printf("Added: %s — %s\n", c.name, c.phone);
            }
        } else {
            printf("Invalid format. Use: name,phone  (e.g. Alice,555-1234)\n");
        }
    }

    printf("\nGoodbye!\n");
    contactlist_free(&list);
    return EXIT_SUCCESS;
}
