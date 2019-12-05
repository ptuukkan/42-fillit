/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:00:53 by avornane          #+#    #+#             */
/*   Updated: 2019/11/25 15:00:57 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_tetlist	*create_tetromino(char **array)
{
	t_tetlist	*new;

	if (!(new = (t_tetlist *)ft_memalloc(sizeof(t_tetlist))))
		exit_error("List allocation failed");
	new->positions = NULL;
	new->next = NULL;
	new->placed_before = 0;
	convert_tetromino(array, new);
	return (new);
}

void				append_tetromino(char **array, t_tetlist **tetrominoes)
{
	t_tetlist	*temp;

	if (*tetrominoes == NULL)
	{
		*tetrominoes = create_tetromino(array);
		return ;
	}
	temp = *tetrominoes;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = create_tetromino(array);
}
