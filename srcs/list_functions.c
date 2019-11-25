#include "fillit.h"

static t_tetlist	*create_tetromino(char **array)
{
	t_tetlist	*new;

	if (!(new = (t_tetlist *)ft_memalloc(sizeof(t_tetlist))))
		exit_error("List allocation failed");
	new->positions = NULL;
	new->next = NULL;
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

static t_poslist	*create_position(int **tetromino)
{
	t_poslist	*new;

	if (!(new = (t_poslist *)ft_memalloc(sizeof(t_poslist))))
		exit_error("List allocation failed");
	new->position[0][0] = tetromino[0][0];
	new->position[0][1] = tetromino[0][1];
	new->position[1][0] = tetromino[1][0];
	new->position[1][1] = tetromino[1][1];
	new->position[2][0] = tetromino[2][0];
	new->position[2][1] = tetromino[2][1];
	new->position[3][0] = tetromino[3][0];
	new->position[3][1] = tetromino[3][1];
	new->usable = 1;
	new->next = NULL;
	return (new);
}

void				append_position(int **tetromino, t_poslist **positions)
{
	t_poslist		*temp;

	if (*positions == NULL)
	{
		*positions = create_position(tetromino);
		return ;
	}
	temp = *positions;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = create_position(tetromino);
}