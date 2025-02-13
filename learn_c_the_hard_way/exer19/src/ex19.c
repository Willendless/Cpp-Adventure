#include "debug.h"
#include <stdlib.h>
#include <stdio.h>

void test_debug()
{
    debug("I have Brown Hair.");
    debug("I am %d years, old.", 37);
}

void test_log_err()
{
    log_err("hello world error");
    log_err("This is a error %s.", "?");
}

void test_log_warn()
{
    log_warn("hello world warning");
    log_warn("THis is a warning %s.", "?");
}

void test_log_info()
{
    log_info("hello world info");
    log_info("THis is a info %s.", "?");
}

int test_check(char *file_name)
{
    FILE *input = NULL;
    char *block = NULL;

    block = malloc(100);
    check_mem(block);

    input = fopen(file_name, "r");
    check(input, "Failed to open %s.", file_name);

    free(block);
    fclose(input);
    return 0;

error:
    if (block) free(block);
    if (input) fclose(input);
    return -1;
}

int test_sentinel(int code)
{
    char *temp = malloc(100);
    check_mem(temp);

    switch (code) {
    case 1:
        log_info("It worked.");
        break;
    default:
        sentinel("Unreached code.");
    }

    free(temp);
    return 0;

error:
    if (temp)
        free(temp);
    return -1;
}

int test_check_mem()
{
    char *test = NULL;
    check_mem(test);

    free(test);
    return 1;
error:
    return -1;
}

int test_check_debug()
{
    int i = 0;
    check(i != 0, "Oops, I was 0.")

    return 0;
error:
    return -1;
}

int main(int argc, char* argv[])
{
    check(argc == 2, "should be 2 arguments")

    test_debug();
    test_log_err();
    test_log_warn();
    test_log_info();

    check(test_check("ex19.c") == 0, "failed with ex19.c");
    check(test_check(argv[1]) == -1, "failed with ex19.c");
    check(test_sentinel(1) == 0, "test_sentinel failed.");
    check(test_sentinel(100) == -1, "test_sentinel failed.");
    check(test_check_mem() == -1, "test_check_mem failed.");
    check(test_check_debug() == -1, "test_check_debug failed.");

    return 0;

error:
    return 1;
}
