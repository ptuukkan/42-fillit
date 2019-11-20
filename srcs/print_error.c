#include "fillit.h"

int		print_error(void)
{
	write(1, "error\n", 6);
	return (-1);
}

void	exit_error(void)
{
	print_error();
	exit(-1);
}