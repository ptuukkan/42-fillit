#include "fillit.h"

int print_error()
{
	write(1, "error\n", 6);
	return (-1);
}