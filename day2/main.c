#include	<unistd.h> // read()
#include	<fcntl.h> // open()
#include	<stdio.h> // printf()
#define		BUFFER_SIZE 15000

int	compare_inputs(char elf, char you)
{
	int	score = 0;

	you -= 23;
	if (you == 'A')
		score += 1;
	else if (you == 'B')
		score += 2;
	else if (you == 'C')
		score += 3;

	if (elf == you)
		score += 3;
	else if ((elf == 'A' && you == 'C') || (elf == 'B' && you == 'A') || (elf == 'C' && you == 'B'))
		score += 0;
	else
		score += 6;
	return (score);
}

int	calculate_score(char *buf)
{
	int	i = 0;
	int total = 0;

	while (buf[i] != '\0')
	{
		total += compare_inputs(buf[i], buf[i+2]);
		i += 4;
	}
	return (total);
}

int	main(void)
{
	char	buf[BUFFER_SIZE + 1];
	int		answer = 0;

	int fd = open("input.txt", O_RDONLY);
	read(fd, buf, BUFFER_SIZE);

	answer = calculate_score(buf);
	printf("%i\n", answer);
}
