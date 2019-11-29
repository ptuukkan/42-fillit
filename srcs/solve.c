#include "fillit.h"

/*
**	Laita ensimmäinen pala ensimmäiseen mahdolliseen positioon
**		- Käy seuraavat palat läpi ja merkkaa kyseinen positio käyteteyksi
**	Siirry seuraavaan palaan ja tee sama uudestaan.
*/


int		solve(t_tetlist *tetromino, int sqr_size)
{
	char	map[sqr_size][sqr_size];
	// if no more pieces left, return 1 else.
	if (tetromino->next == NULL)
			return (1);
	
	// Add piece to to map
	
	// Mark position as used to all other pieces

}
