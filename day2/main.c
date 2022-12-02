#include	<unistd.h> // read()
#include	<fcntl.h> // open()
#include	<stdio.h> // printf()
#define		BUFFER_SIZE 15000

// A = rock, B = paper, C = scissors
int	compare_inputs_p1(char elf, char you)
{
	int	score = 0;

	you -= 23; // Convert XYZ column to ABC for clarity
	score += you - 64; // I love ASCII values (value of 'A' is 65)

	if (elf == you) // draw
		score += 3;
	else if ((elf == 'A' && you == 'C') || (elf == 'B' && you == 'A') || (elf == 'C' && you == 'B')) // loss
		score += 0;
	else // win
		score += 6;
	return (score);
}

// X = loss, Y = draw, Z = win
int compare_inputs_p2(char elf, char result)
{
	int	score = 0;

	if (result == 'Y') // draw
		score += elf - 64 + 3;
	else if (result == 'X') // loss
	{
		if (elf == 'A')
			score += 3;
		if (elf == 'B')
			score += 1;
		if (elf == 'C')
			score += 2;
	}
	else if (result == 'Z') // winner
	{
		if (elf == 'A')
			score += 8;
		if (elf == 'B')
			score += 9;
		if (elf == 'C')
			score += 7;
	}
	return (score);
}

int	calculate_score(char *buf, int part)
{
	int	i = 0;
	int total = 0;

	while (buf[i] != '\0')
	{
		if (part == 1)
			total += compare_inputs_p1(buf[i], buf[i+2]);
		if (part == 2)
			total += compare_inputs_p2(buf[i], buf[i+2]);
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

	answer = calculate_score(buf, 1);
	printf("%i\n", answer);
	answer = calculate_score(buf, 2);
	printf("%i\n", answer);
}
