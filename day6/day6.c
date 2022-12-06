#include	<unistd.h> // read()
#include	<fcntl.h> // open()
#include	<stdio.h> // printf()
#define		BUFFER_SIZE 15000

int	compare(char *section)
{
	int i = 0;
	int j;

	while (i < 13)
	{
		j = 1;
		while (j < 14 - i)
		{
			if (section[i] == section[i+j])
				return(0);
			j++;
		}
		i++;
	}
	return (1);
}

int	traverse_p2(char *buf)
{
	int i = 0;

	while(1)
	{
		if(compare(buf + i))
			return (i + 14);
		i++;
	}
}

int	traverse_p1(char *buf)
{
	int i = 3;

	while(1)
	{
		if(buf[i] != buf[i - 1] && buf[i] != buf[i - 2] && buf[i] != buf[i - 3])
			if(buf[i - 1] != buf[i - 2] && buf[i - 1] != buf[i - 3])
				if(buf[i - 2] != buf[i - 3])
					return (i + 1);
		i++;
	}
}

int	main(void)
{
	int fd = open("input.txt", O_RDONLY);
	char buf[BUFFER_SIZE + 1];
	int answer;

	read(fd, buf, BUFFER_SIZE);
	answer = traverse_p1(buf);
	printf("part1: %i\n", answer);
	answer = traverse_p2(buf);
	printf("part2: %i\n", answer);
}