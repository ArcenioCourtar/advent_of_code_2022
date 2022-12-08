#include	<unistd.h> // read()
#include	<fcntl.h> // open()
#include	<stdio.h> // printf()
#define		BUFFER_SIZE 15000

int	compare_p1(char grid[100][100], int v, int h, int dims)
{
	int iv = 0;
	int ih = 0;
	char highest = '0';
	char current = grid[v][h];

	while (ih < h)
	{
		if (highest < grid[v][ih])
			highest = grid[v][ih];
		ih++;
	}
	if (highest < current)
		return (1);
	highest = '0';
	ih = dims - 1;
	while (ih > h)
	{
		if (highest < grid[v][ih])
			highest = grid[v][ih];
		ih--;
	}
	if (highest < current)
		return (1);
	highest = '0';
	while (iv < v)
	{
		if (highest < grid[iv][h])
			highest = grid[iv][h];
		iv++;
	}
	if (highest < current)
		return (1);
	highest = '0';
	iv = dims - 1;
	while (iv > v)
	{
		if (highest < grid[iv][h])
			highest = grid[iv][h];
		iv--;
	}
	if (highest < grid[v][h])
		return (1);
	return (0);
}

int	compare_p2(char grid[100][100], int v, int h, int dims, int ans2)
{
	int c_left = 0, c_right = 0, c_up = 0, c_down = 0;
	int iv = v - 1;
	int ih = h - 1;
	char current = grid[v][h];

	while (ih >= 0)
	{
		c_left++;
		if (grid[v][ih] >= current)
			break;
		ih--;
	}
	ih = h + 1;
	while (ih < dims)
	{
		c_right++;
		if (grid[v][ih] >= current)
			break;
		ih++;
	}
	while (iv >= 0)
	{
		c_up++;
		if (grid[iv][h] >= current)
			break;
		iv--;
	}
	iv = v + 1;
	while (iv < dims)
	{
		c_down++;
		if (grid[iv][h] >= current)
			break;
		iv++;
	}
	if (ans2 < (c_left * c_right * c_up * c_down))
		return (c_left * c_right * c_up * c_down);
	return (ans2);
}

void find_ans(char grid[100][100], int dims)
{	
	int v = 0;
	int h = 0;
	int ans1 = 0, ans2 = 0;

	while (grid[v][0] != '\0')
	{
		while(grid[v][h] != '\0')
		{
			if (v == 0 || h == 0 || h == dims - 1 || v == dims - 1)
				ans1++;
			else
			{
				ans1 += compare_p1(grid, v, h, dims);
				ans2 = compare_p2(grid, v, h, dims, ans2);
			}
			h++;
		}
		h = 0;
		v++;
	}
	printf("part1: %i\n", ans1);
	printf("part2: %i\n", ans2);
}

void fill_grid(char *buf, char grid[100][100], int dims)
{
	int i = 0;
	int v = 0;
	int mod = dims + 1;
	
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			v++;
		else
			grid[v][i % mod] = buf[i];
		i++;
	}
}

int main(void)
{
	int fd = open("input.txt", O_RDONLY);
	char buf[BUFFER_SIZE + 1];
	char grid[100][100] = {0};
	int dims = 99;

	read(fd, buf, BUFFER_SIZE);
	fill_grid(buf, grid, dims);
	find_ans(grid, dims);
}