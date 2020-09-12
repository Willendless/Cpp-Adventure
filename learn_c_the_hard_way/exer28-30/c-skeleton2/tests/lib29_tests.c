#include "minunit.h"
#include <dlfcn.h>
#include "debug.h"

typedef int (*lib_function) (const char *data, int len);
char *lib_file = "build/libex29.so";
void *lib = NULL;

/*
 * Unit test structured with no arguments and return a char *
 * NULL on success
 */
char *test_dlopen() {
    lib = dlopen(lib_file, RTLD_NOW);
    mu_assert(lib != NULL, "Failed to open the library to test.");
    return NULL;
}

int check_function(const char *func_to_run, const char *data, int expected) {
    lib_function func = dlsym(lib, func_to_run);
    check(func != NULL, "Did not find %s function in the library %s: %s", func_to_run, lib_file, dlerror());
    int rc = func(data, strlen(data));
    check(rc == expected, "Function %s return %d for data: %s", func_to_run, rc,  data);
    return 1;
error:
    return 0;
}

char *test_function() {
    mu_assert(check_function("print_a_message", "Hello", 0), "print_a_message failed");
    mu_assert(check_function("uppercase", "Hello", 0), "uppercase failed");
    mu_assert(check_function("lowercase", "Hello", 0), "lowercase failed");
    return NULL;
}

char *test_failure() {
    mu_assert(check_function("fail_on_purpose", "Hello", 1), "fail_on_purpose should fail");
    return NULL;
}

char *test_dlclose() {
    int rc = dlclose(lib);
    mu_assert(rc == 0, "Failed to close lib.")
    return NULL;
}


/*
 * Runner function
 */
char *all_tests() {
    mu_suite_start();

    mu_run_test(test_dlopen);
    mu_run_test(test_function);
    mu_run_test(test_failure);
    mu_run_test(test_dlclose);
    
    return NULL;
}

RUN_TESTS(all_tests);

// typedef int (*lib_function) (const char *data, int len);

// int main(int argc, char *argv[]) {
//     int rc = 0;
//     // check(argc == 4, "USAGE: ex29 libex29.so function data");

//     char *lib_file = "./build/libex29.so";
//     char *func_to_run = "uppercase";
//     char *data = "I can see you!!!";

//     void *lib = dlopen(lib_file, RTLD_NOW);
//     check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

//     lib_function func = dlsym(lib, func_to_run);
//     check(func != NULL, "Did not find %s function in the library %s: %s", func_to_run, lib_file, dlerror());

//     rc = func(data, strlen(data));
//     check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);

//     rc = dlclose(lib);
//     check(rc == 0, "Failed to close %s", lib_file);

//     return 0;
// error:
//     return 1;
// }
