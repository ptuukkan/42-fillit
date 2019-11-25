/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_positions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:00:53 by avornane          #+#    #+#             */
/*   Updated: 2019/11/25 15:00:57 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		max_width(int **tetromino)
{
	int	m;
	int	i;

	i = 1;
	m = tetromino[0][1];
	while (i < 4)
	{
		if (tetromino[i][1] > m)
			m = tetromino[i][1];
		i++;
	}
	return (m);
}

int		max_length(int **tetromino)
{
	int	m;
	int	i;

	i = 1;
	m = tetromino[1][0];
	while (i < 4)
	{
		if (tetromino[1][i] > m)
			m = tetromino[1][i];
		i++;
	}
	return (m);
}

void	fill_positions(int **tetromino, t_poslist *positions, int sqr_size)
{
	int	tetcopy[4][2];
	int	lx;
	int	ly;

	ly = max_length(tetromino);
	tetcopy[0][0] = tetromino[0][0];
	tetcopy[1][0] = tetromino[1][0];
	tetcopy[2][0] = tetromino[2][0];
	tetcopy[3][0] = tetromino[3][0];
	if (positions == NULL)
	{
		while (ly < sqr_size)
		{
			tetcopy[0][1] = tetromino[0][1];
			tetcopy[1][1] = tetromino[1][1];
			tetcopy[2][1] = tetromino[2][1];
			tetcopy[3][1] = tetromino[3][1];
			lx = max_width(tetromino); 
			while (lx < sqr_size)
			{
				append_position(tetcopy, &positions);
				tetcopy[0][1]++;
				tetcopy[1][1]++;
				tetcopy[2][1]++;
				tetcopy[3][1]++;
				lx++;
			}
			tetcopy[0][0]++;
			tetcopy[1][0]++;
			tetcopy[2][0]++;
			tetcopy[3][0]++;
			ly++;
		}
	}
}

void	calculate_positions(t_tetlist *tetrominoes, int sqr_size)
{
	while (tetrominoes)
	{
		fill_positions(tetrominoes->tetromino, tetrominoes->positions, sqr_size);
		tetrominoes = tetrominoes->next;
	}
	
}