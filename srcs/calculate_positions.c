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
	int	tetcopy[4][2];
	int	lx;
	int	ly;

	ly = max_length(tetromino);
	lx = 0;
	tetcopy[0][0] = tetromino[0][0];
	tetcopy[1][0] = tetromino[1][0];
	tetcopy[2][0] = tetromino[2][0];
	tetcopy[3][0] = tetromino[3][0];
//if (*positions == NULL)
//	{
		while (ly < sqr_size)
		{
			tetcopy[0][1] = tetromino[0][1];
			tetcopy[1][1] = tetromino[1][1];
			tetcopy[2][1] = tetromino[2][1];
			tetcopy[3][1] = tetromino[3][1];
			lx = max_width(tetromino); 
			while (lx < sqr_size)
			{
				append_position(tetcopy, positions);
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
//	}
}

void	calculate_new_positions(t_tetlist *tetrominoes, int sqr_size)
{
	int			row;
	t_poslist	*temp;

	row = 0;
	while (tetrominoes)
	{
		while (tetrominoes->positions)
		{
			while (tetrominoes->positions->next && tetrominoes->positions->next->position[0][0] == row)
				tetrominoes->positions = tetrominoes->positions->next;
			temp = tetrominoes->positions->next;
			tetrominoes->positions->next = create_position();
			tetrominoes->positions->next->next = temp;
			tetrominoes->positions = tetrominoes->positions->next->next;
			row++;
		}
		uudelle riville kaikki elementit
	}
}

0.0 -> 0.1 -> 0.2 -> 0.3 -> 0.4 ->
1.0 -> 1.1 -> 1.2 -> 1.3 -> 1.4 -> 
2.0 -> 2.1 -> 2.2 -> 2.3 -> 2.4 -> NULL


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


Kelataan positiolistaa niin kauan kunnes positions->next->position[0][0] > nykyinen rivi
	- yks positio väliin, vaihda riviä
