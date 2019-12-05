/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_validate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:42:20 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/04 11:42:22 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Counts neighbor blocks for each block.
** Valid tetromino contains 6 or 8 neighbors.
*/

static int	count_neighbours(char **array, int x, int y)
{
	int result;

	result = 0;
	if (y > 0 && array[y - 1][x] == '#')
		result++;
	if (y < 3 && array[y + 1][x] == '#')
		result++;
	if (x > 0 && array[y][x - 1] == '#')
		result++;
	if (x < 3 && array[y][x + 1] == '#')
		result++;
	return (result);
}

/*
** Checks that each line is 4 chars long, contains only . and #,
** has four lines and contains only 4 blocks.
*/

static void	validate_tetromino(char **array)
{
	int	y;
	int	x;
	int	t;
	int tet;

	y = 0;
	t = 0;
	tet = 0;
	while (array[y] != NULL)
	{
		x = 0;
		while (array[y][x] != '\0')
		{
			if (array[y][x] != '.' && array[y][x] != '#')
				exit_error();
			if (array[y][x] == '#')
			{
				t++;
				tet += count_neighbours(array, x, y);
			}
			x++;
		}
		if (x != 4)
			exit_error();
		y++;
	}
	if (t != 4 || y != 4 || tet < 6)
		exit_error();
}

/*
** Reads until 5 lines or eof. Makes sure that fifth line is '\0'.
** Copies each line to 2d char array passed as parameter.
** Returns number of lines read.
*/

static int	read_tetromino(int fd, char **array)
{
	char	*line;
	int		i;
	int		ret;

	i = 0;
	while (i < 5 && (ret = get_next_line(fd, &line)))
	{
		if (i == 4)
		{
			if (*line != '\0')
				exit_error();
			if (line)
				ft_strdel(&line);
		}
		else
			array[i] = line;
		i++;
	}
	if (i != (4 + ret))
	{
		while (i--)
			ft_strdel(&array[i]);
		free(array);
	}
	return (i);
}

/*
** Loops the read_tetromino function until lines read is 0 == EOF.
** Initializes fresh 2d array for each tetromino.
** Counts tetrominoes and total number of lines read.
** Tetromino count must be >=1  && <= 26.
** Number of lines read must be tetromino count * 5 - 1.
*/

int			read_file(int fd, t_tetlist **tetrominoes)
{
	char	**array;
	int		tet_count;
	int		lines_read;
	int		ret;

	lines_read = 0;
	tet_count = 0;
	ret = 0;
	array = init_array();
	while ((ret = read_tetromino(fd, array)) > 0)
	{
		validate_tetromino(array);
		append_tetromino(array, tetrominoes);
		del_array(array);
		free(array);
		array = init_array();
		tet_count++;
		lines_read += ret;
	}
	if (tet_count < 1 || tet_count > 26)
		exit_error();
	if (lines_read != (tet_count * 5 - 1))
		exit_error();
	return (tet_count);
}
