#include	<unistd.h> // read()
#include	<fcntl.h> // open()
#include	<stdio.h> // printf()
#include	<ctype.h> // isdigit()
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

int	compare_p1(int *numlist)
{
	if (numlist[0] <= numlist[2] && numlist[1] >= numlist[3])
		return (1);
	else if (numlist[0] >= numlist[2] && numlist[1] <= numlist[3])
		return (1);
	return (0);
}

int compare_p2(int *numlist)
{
	int sections[100] = {0};
	int i = numlist[0];

	while (i <= numlist[1])
	{
		sections[i] = 1;
		i++;
	}
	i = numlist[2];
	while (i <= numlist[3])
	{
		if (sections[i] == 1)
			return (1);
		i++;
	}
	return (0);
}

void	calculate(char *buf)
{
	int i = 0;
	int totals_p1 = 0;
	int totals_p2 = 0;
	int numlist[4] = {0};
	int num_i = 0;

	while (buf[i] != '\0')
	{
		if ((i == 0 || buf[i - 1] == '\n' || buf[i - 1] == '-' || buf[i - 1] == ',') && isdigit(buf[i]) != 0)
		{
			numlist[num_i] = atoi_mini(buf + i);
			num_i++;
		}
		if (num_i == 4)
		{
			totals_p1 += compare_p1(numlist);
			totals_p2 += compare_p2(numlist);
			num_i = 0;
		}
		i++;
	}
	printf("part1: %i\npart2: %i", totals_p1, totals_p2);
}

int	main(void)
{
	int		fd = open("input.txt", O_RDONLY);
	char	buf[BUFFER_SIZE + 1];

	read(fd, buf, BUFFER_SIZE);
	calculate(buf);
}