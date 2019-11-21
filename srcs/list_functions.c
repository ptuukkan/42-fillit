#include "fillit.h"

static t_tetlist	*create_tetromino(char **array)
{
	t_tetlist	*new;

	if (!(new = (t_tetlist *)ft_memalloc(sizeof(t_tetlist))))
		exit_error();
	new->tetromino = array;
	new->positions = NULL;
	new->next = NULL;
	return (new);
}


void				append_tetromino(char **array, t_tetlist **tetrominos)
{
	t_tetlist	*temp;
	t_tetlist	*new;

	if (*tetrominos == NULL)
	{
		*tetrominos = create_tetromino(array);
		return ;
	}
	temp = *tetrominos;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = create_tetromino(array);
}
