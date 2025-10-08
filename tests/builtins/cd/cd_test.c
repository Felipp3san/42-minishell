#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// declare your function
int builtin_cd(char **path);

void run_test(const char *name, char **path)
{
    char cwd[512];

    printf("=== %s ===\n", name);
    if (getcwd(cwd, sizeof(cwd)))
        printf("Before: %s\n", cwd);

    if (builtin_cd(path) == 0)
    {
        if (getcwd(cwd, sizeof(cwd)))
            printf("After:  %s\n", cwd);
        else
            perror("getcwd");
    }
    printf("--------------\n");
}

int main(void)
{
    char *home = getenv("HOME");
    if (!home)
    {
        fprintf(stderr, "HOME not set. Set it before running tests.\n");
        return 1;
    }

    char *test1[] = {NULL};               // cd (no args) → HOME
    char *test2[] = {"/", NULL};          // cd /
    char *test3[] = {"..", NULL};         // cd ..
    char *test4[] = {"/tmp", NULL};       // cd /tmp
    char *test5[] = {"nonexistent", NULL}; // cd nonexistent

    run_test("cd (no args) → HOME", test1);
    run_test("cd /", test2);
    run_test("cd ..", test3);
    run_test("cd /tmp", test4);
    run_test("cd nonexistent", test5);

    return 0;
}

