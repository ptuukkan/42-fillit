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

void	remove_last_position(t_uplist **used_positions, t_poslist *positions)
{
	int			i;
	t_uplist	*tmp;

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
		if (ft_memcmp(positions->position[0], used_positions->xy, sizeof(int) * 2) == 0)
			return (1);
		if (ft_memcmp(positions->position[1], used_positions->xy, sizeof(int) * 2) == 0)
			return (1);
		if (ft_memcmp(positions->position[2], used_positions->xy, sizeof(int) * 2) == 0)
			return (1);
		if (ft_memcmp(positions->position[3], used_positions->xy, sizeof(int) * 2) == 0)
			return (1);
		used_positions = used_positions->next;
	}
	return (0);
}

int		get_next_position(t_tetlist *tetrominoes, t_uplist **used_positions)
{
	t_poslist	*tmp;

	g_get_next_position_count++;
	tmp = tetrominoes->positions;
	while (tmp && compare_position(tmp, *used_positions))
		tmp = tmp->next;
	if (tmp == NULL)
		return (0);
	tmp->selected = 1;
	add_used_position(tmp->position[0], used_positions);
	add_used_position(tmp->position[1], used_positions);
	add_used_position(tmp->position[2], used_positions);
	add_used_position(tmp->position[3], used_positions);
	return (1);
}

int		solve(t_tetlist *tetrominoes, t_uplist **used_positions, int sqr_size)
{
	g_solve_count++;
	if (tetrominoes == NULL)
		return (1);
	while (get_next_position(tetrominoes, used_positions))
	{
		if (solve(tetrominoes->next, used_positions, sqr_size))
			return (1);
		remove_last_position(used_positions, tetrominoes->positions);
	}
	reset_positions(tetrominoes->positions);
	return (0);
}
