Checkataan oikea määrä argumentteja
Open __FILE__
if (!read and validate())
	return error
calculate possible locations()
arrange pieces()
print pieces()

#include "fillit.h"

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (print_usage());
	if ((fd = open(argv[1], O_RDONLY)) == -1);
		return (print_error());
}