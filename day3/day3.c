#include	<unistd.h> // read()
#include	<fcntl.h> // open()
#include	<stdio.h> // printf()
#define		BUFFER_SIZE 15000

int rucksack_size(char *buf_part)
{
	int i = 0;

	while (buf_part[i] != '\n' && buf_part[i] != '\0')
		i++;
	return (i);
}

int compare_contents_p1(char *buf_part, int size)
{
	int elem_list[52] = {0};
	int i = 0;
	int score = 0;

	while (i < size / 2)
	{
		if (buf_part[i] >= 'a' && buf_part[i] <= 'z')
			elem_list[buf_part[i] - 'a'] = 1;
		else
			elem_list[buf_part[i] - 'A' + 26] = 1;
		i++;
	}
	while (i < size)
	{
		if (buf_part[i] >= 'a' && buf_part[i] <= 'z')
		{
			if (elem_list[buf_part[i] - 'a'] == 1)
				score = buf_part[i] - 'a' + 1;
			elem_list[buf_part[i] - 'a'] = 2;
		}
		else
		{
			if (elem_list[buf_part[i] - 'A' + 26] == 1)
				score = buf_part[i] - 'A' + 27;
			elem_list[buf_part[i] - 'A' + 26] = 2;
		}
		i++;
	}
	return (score);
}

int compare_contents_p2(char* buf, int *i)
{
	int elem_list[52] = {0};
	int bag = 1;
	int score = 0;

	while (bag < 4)
	{
		if (buf[*i] == '\n' || buf[*i] == '\0')
			bag++;
		else if (buf[*i] >= 'a' && buf[*i] <= 'z')
		{
			if (elem_list[buf[*i] - 'a'] == bag - 1 || elem_list[buf[*i] - 'a'] == bag)
				elem_list[buf[*i] - 'a'] = bag;
			if (elem_list[buf[*i] - 'a'] == 3)
				score = buf[*i] - 'a' + 1;
		}
		else
		{
			if (elem_list[buf[*i] - 'A' + 26] == bag - 1 || elem_list[buf[*i] - 'A' + 26] == bag)
				elem_list[buf[*i] - 'A' + 26] = bag;
			if (elem_list[buf[*i] - 'A' + 26] == 3)
				score = buf[*i] - 'A' + 27;
		}
		(*i)++;
	}
	return (score);
}

void calculate(char *buf)
{
	int i = 0;
	int size = 0;
	int totals = 0;

	while (buf[i] != '\0')
	{
		size = rucksack_size(buf + i);
		totals += compare_contents_p1(buf + i, size);
		i += size + 1;
	}
	printf("part1: %i\n", totals);
	totals = 0;
	i = 0;
	while (buf[i] != '\0')
		totals += compare_contents_p2(buf, &i);
	printf("part2: %i\n", totals);
}

int main(void)
{
	char	buf[BUFFER_SIZE + 1];
	int 	answer = 0;

	int fd = open("input.txt", O_RDONLY);
	read(fd, buf, BUFFER_SIZE);
	calculate(buf);
}