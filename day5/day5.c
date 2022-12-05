#include	<unistd.h> // read()
#include	<fcntl.h> // open()
#include	<stdio.h> // printf()
#include	<ctype.h> // isalpha(), isdigit()
#define		BUFFER_SIZE 15000

int	atoi_mini(const char *str)
{
	int	number;

	number = 0;
	while (*str >= '0' && *str <= '9')
	{
		number *= 10;
		number += *str - '0';
		str++;
	}
	return (number);
}

void	stack_setup(char stacks[9][60], char *buf)
{
	int mod = 36;
	int i = 0;
	int j;
	int stack_i;

	while (isdigit(buf[i]) == 0)
	{
		if (isalpha(buf[i]) != 0)
		{
			j = 0;
			stack_i = (i % mod) / 4;
			while (stacks[stack_i][j] != '\0')
				j++;
			while (j > 0)
			{
				stacks[stack_i][j] = stacks[stack_i][j - 1];
				j--;
			}
			stacks[stack_i][j] = buf[i];
		}
		i++;
	}
}

void	move_stacks_p1(char stacks[9][60], int num, int src, int dest)
{
	int i = 0, j = 0;

	while (num > 0)
	{
		i = 0, j = 0;
		while (stacks[src][i] != '\0')
			i++;
		while (stacks[dest][j] != '\0')
			j++;
		if (i > 0) // fsanitize leads to different behaviour?????
			i--;
		stacks[dest][j] = stacks[src][i];
		stacks[src][i] = '\0';
		num--;
	}
}

void	move_stacks_p2(char stacks[9][60], int num, int src, int dest)
{
	int i, j;

	while (1)
	{
		i = 0, j = 0;
		while (stacks[src][i] != '\0')
			i++;
		while (stacks[dest][j] != '\0')
			j++;
		while (num > 0)
		{
			stacks[dest][j] = stacks[src][i - num];
			stacks[src][i - num] = '\0';
			j++;
			num--;
		}
		return ;
	}
}

void	parse_commands(char stacks[9][60], char *buf, int part)
{
	int i = 0;
	int num = 0, src = 0, dest = 0;

	while (buf[i] != 'm')
		i++;
	while (buf[i] != '\0')
	{
		if (num == 0 && isdigit(buf[i]) != 0 && buf[i - 1] == ' ')
			num = atoi_mini(buf + i);
		else if (src == 0 && isdigit(buf[i]) != 0 && buf[i - 1] == ' ')
			src = atoi_mini(buf + i);
		else if (dest == 0 && isdigit(buf[i]) != 0 && buf[i - 1] == ' ' && part == 1)
		{
			dest = atoi_mini(buf + i);
			move_stacks_p1(stacks, num, src - 1, dest - 1);
			src = dest = num = 0;
		}
		else if (dest == 0 && isdigit(buf[i]) != 0 && buf[i - 1] == ' ' && part == 2)
		{
			dest = atoi_mini(buf + i);
			move_stacks_p2(stacks, num, src - 1, dest - 1);
			src = dest = num = 0;
		}
		i++;
	}
}

int	main(void)
{
	int fd = open("input.txt", O_RDONLY);
	char buf[BUFFER_SIZE+1];
	char stacks1[9][60];
	char stacks2[9][60];
	int i = 0;
	
	read(fd, buf, BUFFER_SIZE);
	stack_setup(stacks1, buf);
	stack_setup(stacks2, buf);
	parse_commands(stacks1, buf, 1);
	while (i < 9)
	{
		printf("%s\n", stacks1[i]);
		i++;
	}
	parse_commands(stacks2, buf, 2);
	i = 0;
	printf("\n");
	while (i < 9)
	{
		printf("%s\n", stacks2[i]);
		i++;
	}
}