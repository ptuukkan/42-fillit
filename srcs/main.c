

#include "fillit.h"

void	print_tetrominos(t_tetlist *tetrominos)
{
	while (tetrominos)
	{
		while (*tetrominos->tetromino)
		{
			ft_putendl(*tetrominos->tetromino);
			tetrominos->tetromino++;
		}
		tetrominos = tetrominos->next;
	}
}

int	main(int argc, char **argv)
{
	int			fd;
	t_tetlist	*tetrominos;

	if (argc != 2)
		return (print_usage());
	if ((fd = open(argv[1], O_RDONLY)) == -1);
		return (print_error());
	tetrominos = NULL;
	if (!read_file(fd, &tetrominos))
		return (print_error());
	print_tetrominos(tetrominos);
	return (0);
}
