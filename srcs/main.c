

#include "fillit.h"

void	print_tetrominos(t_tetlist *tetrominoes)
{
	while (tetrominoes)
	{
		printf("A_Y: %d\nA_X: %d\n", tetrominoes->tetromino[0][0], tetrominoes->tetromino[0][1]);
		printf("B_Y: %d\nB_X: %d\n", tetrominoes->tetromino[1][0], tetrominoes->tetromino[1][1]);
		printf("C_Y: %d\nC_X: %d\n", tetrominoes->tetromino[2][0], tetrominoes->tetromino[2][1]);
		printf("D_Y: %d\nD_X: %d\n\n", tetrominoes->tetromino[3][0], tetrominoes->tetromino[3][1]);
		tetrominoes = tetrominoes->next;
	}
}

int	main(int argc, char **argv)
{
	int			fd;
	t_tetlist	*tetrominos;

	if (argc != 2)
		return (print_usage());
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (print_error("file open failed!"));
	tetrominos = NULL;
	if (!read_file(fd, &tetrominos))
		return (print_error("Read file failed!"));
	print_tetrominos(tetrominos);
	return (0);
}
