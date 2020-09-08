#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "debug.h"

int print_a_message(const char *msg, int len) {
    assert(msg != NULL && "input cannot be NULL");
    printf("A STRING: %s\n", msg);
    return 0;
}

int uppercase(const char *msg, int len) {
    assert(msg != NULL && "input cannot be NULL");
    int i = 0;
    for (i = 0; i < len; i++) {
        printf("%c", toupper(msg[i]));
    }
    printf("\n");
    return 0;
}

int lowercase(const char *msg, int len) {
    assert(msg != NULL && "input cannot be NULL");
    int i = 0;
    for (i = 0; i < len && msg[i] != '\0'; i++) {
        printf("%c", tolower(msg[i]));
    }
    printf("\n");
    return 0;
}

int fail_on_purpose(const char *msg, int len) {
    return 1;
}
