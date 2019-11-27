

#include "fillit.h"

void	print_tetrominoes(t_tetlist *tetrominoes)
{
	int	i;

	
	while (tetrominoes)
	{
		printf("Tetromino blocks:\n");
		printf("A_Y: %d\nA_X: %d\n", tetrominoes->tetromino[0][0], tetrominoes->tetromino[0][1]);
		printf("B_Y: %d\nB_X: %d\n", tetrominoes->tetromino[1][0], tetrominoes->tetromino[1][1]);
		printf("C_Y: %d\nC_X: %d\n", tetrominoes->tetromino[2][0], tetrominoes->tetromino[2][1]);
		printf("D_Y: %d\nD_X: %d\n\n", tetrominoes->tetromino[3][0], tetrominoes->tetromino[3][1]);
		i = 1;
		while (tetrominoes->positions)
		{
			printf("Position %d:\n", i);
			printf("A_Y: %d\nA_X: %d\n", tetrominoes->positions->position[0][0], tetrominoes->positions->position[0][1]);
			printf("B_Y: %d\nB_X: %d\n", tetrominoes->positions->position[1][0], tetrominoes->positions->position[1][1]);
			printf("C_Y: %d\nC_X: %d\n", tetrominoes->positions->position[2][0], tetrominoes->positions->position[2][1]);
			printf("D_Y: %d\nD_X: %d\n\n", tetrominoes->positions->position[3][0], tetrominoes->positions->position[3][1]);
			i++;
			tetrominoes->positions = tetrominoes->positions->next;
		}
		tetrominoes = tetrominoes->next;
	}
}

int	calc_min_sqrsize(int tet_count)
{
	int	i;

	i = 2;
	while (i * i < (tet_count * 4))
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_tetlist	*tetrominoes;
	int			sqr_size;
	int			tet_count;

	if (argc != 2)
		return (print_usage());
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (print_error("file open failed!"));
	tetrominoes = NULL;
	if (!(tet_count = read_file(fd, &tetrominoes)))
		return (print_error("Read file failed!"));
	sqr_size = calc_min_sqrsize(tet_count);
	calculate_positions(tetrominoes, sqr_size);
	print_tetrominoes(tetrominoes);
	return (0);
}
