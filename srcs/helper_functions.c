/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:18:27 by avornane          #+#    #+#             */
/*   Updated: 2019/12/05 13:18:28 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Room for 5 string in array. 4 strings for tetromino.
** One for null string.
*/

char	**init_array(void)
{
	char	**array;

	if (!(array = (char **)ft_memalloc(sizeof(char *) * 5)))
		exit_error("Array allocation failed!");
	return (array);
}

void	del_array(char **array)
{
	while (*array)
	{
		ft_strdel(array);
		array++;
	}
	array = NULL;
}

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
