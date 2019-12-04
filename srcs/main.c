/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:00:53 by avornane          #+#    #+#             */
/*   Updated: 2019/11/25 15:00:57 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

unsigned long long	g_solve_count = 0;
unsigned long long	g_get_next_position_count = 0;
unsigned long long	g_compare_position_count = 0;
unsigned long long	g_ft_memcmp_count = 0;
unsigned long long	g_add_used_position_count = 0;
unsigned long long	g_remove_last_position_count = 0;
unsigned long long	g_reset_positions_count = 0;
double	time_eliminate = 0.0;

void	print_positions(t_tetlist *tetrominoes)
{
	int	i;
	t_poslist *tmp;


	while (tetrominoes)
	{
		tmp = tetrominoes->positions;
		printf("Tetromino blocks:\n");
		printf("A_Y: %d\nA_X: %d\n", tetrominoes->tetromino[0][0], tetrominoes->tetromino[0][1]);
		printf("B_Y: %d\nB_X: %d\n", tetrominoes->tetromino[1][0], tetrominoes->tetromino[1][1]);
		printf("C_Y: %d\nC_X: %d\n", tetrominoes->tetromino[2][0], tetrominoes->tetromino[2][1]);
		printf("D_Y: %d\nD_X: %d\n\n", tetrominoes->tetromino[3][0], tetrominoes->tetromino[3][1]);
		i = 1;
		while (tmp)
		{
			printf("Position %d:\n", i);
			printf("A_Y: %d\nA_X: %d\n", tmp->position[0][0], tmp->position[0][1]);
			printf("B_Y: %d\nB_X: %d\n", tmp->position[1][0], tmp->position[1][1]);
			printf("C_Y: %d\nC_X: %d\n", tmp->position[2][0], tmp->position[2][1]);
			printf("D_Y: %d\nD_X: %d\n\n", tmp->position[3][0], tmp->position[3][1]);
			i++;
			tmp = tmp->next;
		}
		tetrominoes = tetrominoes->next;
	}
}

char	**init_map(char **map, int sqr_size)
{
	int i;

	i = 0;
	if (!(map = (char**)ft_memalloc(sizeof(char*) * sqr_size + 1)))
		exit_error("map init failed!");
	while (i < sqr_size)
	{
		if(!(map[i] = ft_strnew(sqr_size)))
			exit_error("Map row allocation failed!");
		ft_memset(map[i], '.', sqr_size);
		i++;
	}
	map[i] = NULL;
	return(map);
}

void	print_map(char **map)
{
	while (*map)
	{
		ft_putendl(*map);
		map++;
	}
}

void	print_tetrominoes(t_tetlist *tetrominoes, int sqr_size)
{
	char **map;
	char c;

	c = 'A';
	map = NULL;
	map = init_map(map, sqr_size);

	while (tetrominoes)
	{
		while (tetrominoes->positions->selected == 0)
			tetrominoes->positions = tetrominoes->positions->next;
		map[tetrominoes->positions->position[0][0]][tetrominoes->positions->position[0][1]] = c;
		map[tetrominoes->positions->position[1][0]][tetrominoes->positions->position[1][1]] = c;
		map[tetrominoes->positions->position[2][0]][tetrominoes->positions->position[2][1]] = c;
		map[tetrominoes->positions->position[3][0]][tetrominoes->positions->position[3][1]] = c;
		c++;
		tetrominoes = tetrominoes->next;
	}
	print_map(map);
}

int	calc_min_sqrsize(int tet_count, t_tetlist *tetrominoes)
{
	int	i;
	int	n;

	if (tet_count > 2)
	{
		i = 2;
		while (i * i < (tet_count * 4))
			i++;
	}
	else
	{
		i = 1 + ft_max(max_width(tetrominoes->tetromino), max_length(tetrominoes->tetromino));
		if (tet_count == 2)
		{
			n = 1 + ft_max(max_width(tetrominoes->next->tetromino), max_length(tetrominoes->next->tetromino));
			i = ft_max(i, n);
		}
	}
	return (i);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_tetlist	*tetrominoes;
	int			sqr_size;
	int			tet_count;
	t_uplist	*used_positions;

	if (argc != 2)
		return (print_usage());
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (print_error("file open failed!"));
	tetrominoes = NULL;
	if (!(tet_count = read_file(fd, &tetrominoes)))
		return (print_error("Read file failed!"));
	sqr_size = calc_min_sqrsize(tet_count, tetrominoes);
	calculate_positions(tetrominoes, sqr_size);
	used_positions = NULL;
	while (solve(tetrominoes, &used_positions, sqr_size) == 0)
	{
		sqr_size++;
		calculate_new_positions(tetrominoes, sqr_size);
		remove_uplist(&used_positions);
	}
	print_tetrominoes(tetrominoes, sqr_size);

	printf("%-30s%20llu\n", "Solve count:", g_solve_count);
	printf("%-30s%20llu\n","Get_next_position count:", g_get_next_position_count);
	printf("%-30s%20llu\n","Eliminate_position count:", g_compare_position_count);
	printf("%-30s%20f\n","Eliminate_position time:", time_eliminate);
	printf("%-30s%20llu\n","Add_used_position count:", g_add_used_position_count);
	printf("%-30s%20llu\n","Remove_last_position count:", g_remove_last_position_count);
	printf("%-30s%20llu\n","Reset_positions count:", g_reset_positions_count);



	return (0);
}
