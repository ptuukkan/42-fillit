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

int		calc_min_sqrsize(int tet_count, t_tetlist *tetrominoes)
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
		i = 1 + ft_max(max_width(tetrominoes->tetromino), \
		max_length(tetrominoes->tetromino));
		if (tet_count == 2)
		{
			n = 1 + ft_max(max_width(tetrominoes->next->tetromino), \
			max_length(tetrominoes->next->tetromino));
			i = ft_max(i, n);
		}
	}
	return (i);
}

int		main(int argc, char **argv)
{
	int			fd;
	t_tetlist	*tetrominoes;
	int			sqr_size;
	int			tet_count;
	t_uplist	*used_positions;

	if (argc != 2)
		return (print_usage());
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		exit_error();
	tetrominoes = NULL;
	tet_count = read_file(fd, argv[1], &tetrominoes);
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
	return (0);
}
