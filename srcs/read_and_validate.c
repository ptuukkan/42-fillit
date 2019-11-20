#include "fillit.h"


void	validate(***array)
{
	int	y;
	int	x;
	int	t;

	y = 0;
	t = 0;
	while (y < 4)
	{
		x = 0;
		while ((*array)[y][x] != '\0')
		{
			if ((*array)[y][x] != '.' || (*array)[y][x] != '#')
				exit_error();
			if ((*array)[y][x] != '#')
				t++;
		}
		if (x != 4)
			exit_error();
	}
	if (t != 4)
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
	return (array);
}

int		read_file(int fd)
{
	char	*line;
	char	**array;
	int		ret;
	int		i;

	i = 0;
	array = init_array();
	while (ret = get_next_line(fd, &line))
	{
		if (i % 5 == 4 && *line != '\0')
			return (-1);
		if (i % 5 == 4)
		{
			array[i % 5] = NULL;
			ft_strdel(&line);
		}
		else
			array[i % 5] = line;
		i++;
		if (i % 5 == 0)
			validate(&array);
	}
	if (ret == -1 || i % 5 != 0)
		return (-1);
}
