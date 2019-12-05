/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:03:47 by avornane          #+#    #+#             */
/*   Updated: 2019/12/05 13:03:51 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static char	**init_map(char **map, int sqr_size)
{
	int i;

	i = 0;
	if (!(map = (char**)ft_memalloc(sizeof(char*) * sqr_size + 1)))
		exit_error();
	while (i < sqr_size)
	{
		if (!(map[i] = ft_strnew(sqr_size)))
			exit_error();
		ft_memset(map[i], '.', sqr_size);
		i++;
	}
	map[i] = NULL;
	return (map);
}

static void	print_map(char **map)
{
	while (*map)
	{
		ft_putendl(*map);
		map++;
	}
}

int			print_usage(void)
{
	write(1, "usage\n", 6);
	return (1);
}

void		exit_error(void)
{
	write(1, "error\n", 6);
	exit(-1);
}

void		print_tetrominoes(t_tetlist *tetrominoes, int sqr_size)
{
	char		**map;
	char		c;
	t_poslist	*tmp;

	c = 'A';
	map = NULL;
	map = init_map(map, sqr_size);
	while (tetrominoes)
	{
		tmp = tetrominoes->positions;
		while (tmp->selected == 0)
			tmp = tmp->next;
		map[tmp->position[0][0]][tmp->position[0][1]] = c;
		map[tmp->position[1][0]][tmp->position[1][1]] = c;
		map[tmp->position[2][0]][tmp->position[2][1]] = c;
		map[tmp->position[3][0]][tmp->position[3][1]] = c;
		c++;
		tetrominoes = tetrominoes->next;
	}
	print_map(map);
	del_array(map);
	free(map);
}
