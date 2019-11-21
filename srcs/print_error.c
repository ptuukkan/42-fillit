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