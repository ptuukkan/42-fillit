#include "fillit.h"

/*
** Checks that each line is 4 chars long, contains only . and #,
** has four lines and contains only 4 blocks.
*/

void	validate_tetromino(char **array)
{
	int	y;
	int	x;
	int	t;

	y = 0;
	t = 0;
	while (array[y] != NULL)
	{
		x = 0;
		while (array[y][x] != '\0')
		{
			if (array[y][x] != '.' || array[y][x] != '#')
				exit_error();
			if (array[y][x] == '#')
			{
				t++;
			}
		}
		if (x != 4)
			exit_error();
	}
	if (t != 4 || y != 4)
		exit_error();
}

/*
** Room for 5 string in array. 4 strings for tetromino.
** One for null string.
*/

char	**init_array(void)
{
	char	**array;

	if (!(array = (char **)ft_memalloc(sizeof(char *) * 5)))
		exit_error();
	array[0] = NULL;
	array[1] = NULL;
	array[2] = NULL;
	array[3] = NULL;
	array[4] = NULL;
	return (array);
}

/*
** Reads until 5 lines or eof. Makes sure that fifth line is '\0'.
** Returns tetromino in 2d array if successfully read four lines.
** Returns null if reading stopped before four lines have been read.
*/

char	**read_tetromino(int fd, char **array)
{
	char	*line;
	int		i;
	int		ret;

	i = 0;
	while ((ret = get_next_line(fd, &line)) && i < 5)
	{
		if (i == 4)
		{
			if (*line != '\0')
				exit_error();
			if (line)
				ft_strdel(&line);
		}
		array[i] = line;
		i++;
	}
	if (i != (4 + ret))
		return (NULL);
	return (array);
}

int		read_file(int fd, t_tetlist **tetrominos)
{
	char	**array;
	int		tet_count;

	tet_count = 0;
	array = init_array();
	while ((array = read_tetromino(fd, array)) != NULL)
	{
		validate_tetromino(array);
		tet_count++;
	}
	return (tet_count);
}
