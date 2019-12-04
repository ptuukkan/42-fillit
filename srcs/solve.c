/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:42:31 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/04 11:42:33 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

extern unsigned long long	g_solve_count;
extern unsigned long long	g_get_next_position_count;
extern unsigned long long	g_compare_position_count;
extern unsigned long long	g_remove_last_position_count;
extern unsigned long long	g_reset_positions_count;
extern double	time_eliminate;

void	remove_last_position(t_uplist **used_positions, t_poslist *positions)
{
	int			i;
	t_uplist	*tmp;

	(void)positions;
	g_remove_last_position_count++;
	i = 0;
	while (i < 4)
	{
		tmp = *used_positions;
		*used_positions = (*used_positions)->next;
		free(tmp);
		tmp = NULL;
		i++;
	}
	while (positions->selected == 0)
		positions = positions->next;
	positions->selected = 0;
	positions->usable = 0;
}

void	reset_positions(t_poslist *positions)
{
	g_reset_positions_count++;
	while (positions)
	{
		positions->usable = 1;
		positions = positions->next;
	}
}

int		compare_position(t_poslist *positions, t_uplist *used_positions)
{
	g_compare_position_count++;
	if (positions->usable == 0)
		return (1);
	while (used_positions)
	{
		if ((!(positions->position[0][0] ^ used_positions->xy[0])) &&
			(!(positions->position[0][1] ^ used_positions->xy[1])))
			return (1);
		if ((!(positions->position[1][0] ^ used_positions->xy[0])) &&
			(!(positions->position[1][1] ^ used_positions->xy[1])))
			return (1);
		if ((!(positions->position[2][0] ^ used_positions->xy[0])) &&
			(!(positions->position[2][1] ^ used_positions->xy[1])))
			return (1);
		if ((!(positions->position[3][0] ^ used_positions->xy[0])) &&
			(!(positions->position[3][1] ^ used_positions->xy[1])))
			return (1);
		used_positions = used_positions->next;
	}
	return (0);
}

int	get_position(t_poslist *positions, t_uplist **used_positions)
{
	t_uplist	*tmp;

	while (positions)
	{
		tmp = *used_positions;
		while (tmp)
		{
			if (positions->position[0][0] ^ tmp->xy[0] &&
				positions->position[0][1] ^ tmp->xy[1] &&
				positions->position[1][0] ^ tmp->xy[0] &&
				positions->position[1][1] ^ tmp->xy[1] &&
				positions->position[2][0] ^ tmp->xy[0] &&
				positions->position[2][1] ^ tmp->xy[1] &&
				positions->position[3][0] ^ tmp->xy[0] &&
				positions->position[3][1] ^ tmp->xy[1])
			{
				positions->selected = 1;
				add_used_position(positions->position, used_positions);
				return (1);
			}
			tmp = tmp->next;
		}
		positions = positions->next;
	}
	return (0);
}

int		get_next_position(t_tetlist *tetrominoes, t_uplist **used_positions)
{
	t_poslist	*tmp;

	g_get_next_position_count++;
	tmp = tetrominoes->positions;

	/*
	if (tetrominoes->placed_before == 0)
	{
		if (get_position(tetrominoes->positions, used_positions))
		{
			tetrominoes->placed_before = 1;
			return (1);
		}
		else
			return (0);
	}
	else
	{
		while (tmp->selected == 0)
			tmp = tmp->next;
		tmp->selected = 0;
		if (get_position(tmp->next, used_positions))
		{
			return (1);
		}
		else
			return (0);
	}
	*/

	//while (tmp && compare_position(tmp, *used_positions))
	//	tmp = tmp->next;

	while (tmp && tmp->usable == 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return (0);
	tmp->selected = 1;
	add_used_position(tmp->position, used_positions);

	return (1);
}



void	eliminate_used_positions(t_poslist *positions, t_uplist *used_positions)
{
	t_uplist	*tmp;
	clock_t		t;

	t = clock();
	g_compare_position_count++;
	while (positions)
	{
		tmp = used_positions;
		while (tmp)
		{
			if ((!(positions->position[0][0] ^ tmp->xy[0])) &&
				(!(positions->position[0][1] ^ tmp->xy[1])))
			{
				positions->usable = 0;
				break;
			}
			if ((!(positions->position[1][0] ^ tmp->xy[0])) &&
				(!(positions->position[1][1] ^ tmp->xy[1])))
			{
				positions->usable = 0;
				break;
			}
			if ((!(positions->position[2][0] ^ tmp->xy[0])) &&
				(!(positions->position[2][1] ^ tmp->xy[1])))
			{
				positions->usable = 0;
				break;
			}
			if ((!(positions->position[3][0] ^ tmp->xy[0])) &&
				(!(positions->position[3][1] ^ tmp->xy[1])))
			{
				positions->usable = 0;
				break;
			}
			tmp = tmp->next;
		}
		positions = positions->next;
	}
	t = clock() - t;
	time_eliminate += ((double)t)/CLOCKS_PER_SEC;
}

int		solve(t_tetlist *tetrominoes, t_uplist **used_positions, int sqr_size)
{
	g_solve_count++;

	if (tetrominoes == NULL)
		return (1);
	eliminate_used_positions(tetrominoes->positions ,*used_positions);
	while (get_next_position(tetrominoes, used_positions))
	{
		if (solve(tetrominoes->next, used_positions, sqr_size))
			return (1);
		remove_last_position(used_positions, tetrominoes->positions);
	}
	reset_positions(tetrominoes->positions);
	//tetrominoes->placed_before = 0;
	return (0);
}
