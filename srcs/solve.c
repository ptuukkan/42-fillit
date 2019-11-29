#include "fillit.h"

/*

*/
void	remove_last_position(t_uplist **used_positions, t_poslist *positions)
{
	int			i;
	t_uplist	*tmp;

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
	while (positions)
	{
		positions->usable = 1;
		positions = positions->next;
	}
}

int		compare_position(t_poslist *positions, t_uplist *used_positions)
{
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
	if (used_positions == NULL)
		tetrominoes->positions->selected = 1;
	else
	{
		while (tetrominoes->positions && compare_position(tetrominoes->positions, used_positions))
			tetrominoes->positions = tetrominoes->positions->next;
		if (tetrominoes->positions == NULL)
			return (0);
		tetrominoes->positions->selected = 1;
	}
	add_used_position(tetrominoes->positions->position[0], used_positions);
	add_used_position(tetrominoes->positions->position[1], used_positions);
	add_used_position(tetrominoes->positions->position[2], used_positions);
	add_used_position(tetrominoes->positions->position[3], used_positions);
	return (1);
}

int		solve(t_tetlist *tetrominoes, t_uplist **used_positions, int sqr_size)
{
	if (tetrominoes == NULL)
		return (1);
	while (get_next_position(tetrominoes, used_positions))
	{
		if (solve(tetrominoes->next, used_positions, sqr_size))
			return (1);
		remove_last_position(&used_positions, tetrominoes->positions);
	}
	reset_positions(tetrominoes->positions);
	return (0);
}
