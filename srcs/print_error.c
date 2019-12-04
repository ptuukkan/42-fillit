/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:41:50 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/04 11:41:52 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		print_error(char *str)
{
	write(1, "error\n", 6);
	ft_putendl(str);
	return (-1);
}

void	exit_error(char *str)
{
	write(1, "error\n", 6);
	ft_putendl(str);
	exit(-1);
}
