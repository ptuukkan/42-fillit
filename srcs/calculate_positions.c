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

int		max_width(int tetromino[4][2])
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

int		max_length(int tetromino[4][2])
{
	int	m;
	int	i;

	i = 1;
	m = tetromino[1][0];
	while (i < 4)
	{
		if (tetromino[i][0] > m)
			m = tetromino[i][0];
		i++;
	}
	return (m);
}

void	fill_positions(int tetromino[4][2], t_poslist **positions, int sqr_size)
{
	int	lx;
	int	ly;
	int	y_incr;
	int	x_incr;

	ly = max_length(tetromino);
	lx = 0;
	y_incr = 0;
	while (ly < sqr_size)
	{
		x_incr = 0;
		lx = max_width(tetromino); 
		while (lx < sqr_size)
		{
			append_position(tetromino, positions, y_incr, x_incr);
			x_incr++;
			lx++;
		}
		y_incr++;
		ly++;
	}
}

void	calculate_last_row(int tetromino[4][2], int sqr_size, int row, t_poslist **positions)
{
	int			lx;
	int			x_incr;
	
	x_incr = 0;
	lx = max_width(tetromino);
	while (lx < sqr_size)
	{
		append_position(tetromino, positions, row, x_incr);
		x_incr++;
		lx++;
	}
}

void	calculate_new_positions(t_tetlist *tetrominoes, int sqr_size)
{
	int			row;
	int			x_incr;
	t_poslist	*temp;
	t_poslist	*temp2;

	while (tetrominoes)
	{
		row = 0;
		temp2 = tetrominoes->positions;
		while (temp2)
		{
			x_incr = 1;
			while (temp2->next && temp2->next->position[0][0] == row)
			{
				temp2 = temp2->next;
				x_incr++;
			}
			temp = temp2->next;
			temp2->next = create_position(tetrominoes->tetromino, row, x_incr);
			temp2->next->next = temp;
			temp2 = temp2->next->next;
			row++;
		}
		calculate_last_row(tetrominoes->tetromino, sqr_size, row, &tetrominoes->positions);
		tetrominoes = tetrominoes->next;
	}
}

void	calculate_positions(t_tetlist *tetrominoes, int sqr_size)
{
	t_tetlist	*temp;

	temp = tetrominoes;
	while (temp)
	{
		fill_positions(temp->tetromino, &temp->positions, sqr_size);
		temp = temp->next;
	}
}
