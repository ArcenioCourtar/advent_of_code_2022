#include	<unistd.h> // read()
#include	<fcntl.h> // open()
#include	<stdio.h> // printf()
#include	<ctype.h> // isalpha(), isdigit()
#define		BUFFER_SIZE 15000

void	stack_setup(char stacks[9][60], char *buf)
{
	int i = 0;

	while (isdigit(buf[i]) == 0)
	{
		if (isalpha(buf[i]) != 0)
		{
			stacks[i / 4][0];
			printf("%c", stacks[i / 4][0]);
		}
		i++;
	}
}

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char buf[BUFFER_SIZE+1];
	char stacks[9][60];
	
	read(fd, buf, BUFFER_SIZE);
	stack_setup(stacks, buf);
}