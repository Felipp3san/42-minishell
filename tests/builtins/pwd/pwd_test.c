
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	builtin_pwd(int fd);

int main(void)
{
	int fd = open("test1.txt", O_RDWR);
	printf("%d\n", fd);
	builtin_pwd(fd);
	builtin_pwd(0);
	builtin_pwd(1);
	builtin_pwd(2);
	close(fd);
	return (0);
}
