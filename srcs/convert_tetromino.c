/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tetromino.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:57:12 by avornane          #+#    #+#             */
/*   Updated: 2019/11/25 13:57:18 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	empty_rows(char **array)
{
	int y;
	int x;

	y = 0;
	while (array[y] != NULL)
	{
		x = 0;
		while (array[y][x] != '\0')
		{
			if (array[y][x] == '#')
				return (y);
			x++;
		}
		y++;
	}
	return (0);
}

static int	empty_columns(char **array)
{
	int y;
	int x;

	x = 0;
	y = 0;
	while (array[y][x] != '\0')
	{
		while (array[y] != NULL)
		{
			if (array[y][x] == '#')
				return (x);
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
}

void		convert_tetromino(char **array, t_tetlist *tetrominoes)
{
	int y;
	int x;
	int start_y;
	int start_x;
	int	i;

	start_x = empty_columns(array);
	start_y = empty_rows(array);
	y = start_y;
	i = 0;
	while (array[y] != NULL)
	{
		x = start_x;
		while (array[y][x] != '\0')
		{
			if (array[y][x] == '#')
			{
				tetrominoes->tetromino[i][0] = y - start_y;
				tetrominoes->tetromino[i][1] = x - start_x;
				i++;
			}
			x++;
		}
		y++;
	}
}
