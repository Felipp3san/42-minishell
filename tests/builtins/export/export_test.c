#include "types.h"
#include "minishell.h"
#include <stdio.h>

int	builtin_export(t_list **env, const char *variable);

void print_list(t_list *lst)
{
    while (lst)
    {
		char *print = (char *)lst->content;
        printf("%s\n", print);
        lst = lst->next;
    }
}

void free_list(t_list *lst)
{
    t_list *tmp;
    while (lst)
    {
        tmp = lst->next;
        free(lst->content);
        free(lst);
        lst = tmp;
    }
}

int	main(void)
{
	t_list	*env = NULL;
	int		ret_value;

	// Initial environment
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("PATH=/usr/bin")));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("HOME=/Users/foo")));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("SHELL=/bin/bash")));

	printf("=== Initial environment ===\n");
	print_list(env);

	// Test 1: Replace existing variable
	ret_value = builtin_export(&env, "HOME=/user/home");
	printf("\nAfter exporting HOME=/user/home (replace):\n");
	print_list(env);

	// Test 2: Add a new variable
	ret_value = builtin_export(&env, "CCB=/get/good");
	printf("\nAfter exporting CCB=/get/good (add new):\n");
	print_list(env);

	// Test 3: Add variable without value
	ret_value = builtin_export(&env, "NEWVAR");
	printf("\nAfter exporting NEWVAR (no value):\n");
	print_list(env);

	// Test 4: Invalid variable name
	ret_value = builtin_export(&env, "1INVALID=oops");
	printf("\nAfter exporting 1INVALID=oops (invalid):\n");
	if (ret_value != SUCCESS)
		printf("Error: Invalid variable name\n");
	print_list(env);

	// Test 5: Add variable with underscore and numbers
	ret_value = builtin_export(&env, "VAR_123=value123");
	printf("\nAfter exporting VAR_123=value123:\n");
	print_list(env);

	// Test 6: Replace variable again
	ret_value = builtin_export(&env, "CCB=/get/better");
	printf("\nAfter exporting CCB=/get/better (replace):\n");
	print_list(env);

	// Clean up
	free_list(env);
	return 0;
}