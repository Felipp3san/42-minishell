#include <stdio.h>
#include <string.h>
#include <unistd.h>

// declare your builtin_echo function
int builtin_echo(char **args, int fd);

void run_test(char *name, char **args)
{
    printf("=== %s ===\n", name);
    builtin_echo(args, STDOUT_FILENO);
    printf("\n--------------\n");
}

int main(void)
{
    char *test1[] = {NULL};                               // echo
    char *test2[] = {"hello", NULL};                      // echo hello
    char *test3[] = {"hello", "world", NULL};             // echo hello world
    char *test4[] = {"-n", "hello", NULL};                // echo -n hello
    char *test5[] = {"-n", "hello", "world", NULL};       // echo -n hello world
    char *test6[] = {"-nnn", "hello", NULL};              // echo -nnn hello
    char *test7[] = {"-n", NULL};                         // echo -n
    char *test8[] = {"--", "hello", NULL};                // echo -- hello
    char *test9[] = {"-n", "--", "hello", NULL};          // echo -n -- hello
    char *test10[] = {"-n", "test", "with", "spaces", NULL}; // echo -n test with spaces

    run_test("echo", test1);
    run_test("echo hello", test2);
    run_test("echo hello world", test3);
    run_test("echo -n hello", test4);
    run_test("echo -n hello world", test5);
    run_test("echo -nnn hello", test6);
    run_test("echo -n", test7);
    run_test("echo -- hello", test8);
    run_test("echo -n -- hello", test9);
    run_test("echo -n test with spaces", test10);

    return 0;
}

