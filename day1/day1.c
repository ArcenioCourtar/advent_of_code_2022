#include	<unistd.h> // read()
#include	<fcntl.h> // open()
#include	<stdio.h> // printf()
#include	<ctype.h> // isdigit()
#define		BUFFER_SIZE 15000

int	atoi_for_calories(const char *str)
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

// I love pointers xd
void	sort_calories(int totals, int **n1, int **n2, int **n3)
{
	if (totals > **n1)
	{
		**n3 = **n2;
		**n2 = **n1;
		**n1 = totals;
	}
	else if (totals > **n2)
	{
		**n3 = **n2;
		**n2 = totals;
	}
	else if (totals > **n3)
		**n3 = totals;
}

// For the else if, I could also add an additional newline to the input file,
// instead of checking for \0, lol
void	calculate_calories(char *buf, int *n1, int *n2, int *n3)
{
	int	i = 0;
	int	totals = 0;

	while (buf[i] != '\0')
	{
		if ((i == 0 || buf[i - 1] == '\n') && isdigit(buf[i]) != 0)
			totals += atoi_for_calories(buf + i);
		else if (buf[i] == '\n' && (buf[i + 1] == '\n' || buf[i + 1] == '\0'))
		{
			sort_calories(totals, &n1, &n2, &n3);
			totals = 0;
		}
		i++;
	}
}

int	main(void)
{
	int		fd = open("input.txt", O_RDONLY);
	char	buf[BUFFER_SIZE + 1];
	int		n1 = 0;
	int		n2 = 0;
	int		n3 = 0;

	read(fd, buf, BUFFER_SIZE);
	calculate_calories(buf, &n1, &n2, &n3);
	printf("%i + %i + %i = %i\n", n1, n2, n3, (n1 + n2 + n3));
}
