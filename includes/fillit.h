#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
# include <fcntl.h>

typedef struct			s_poslist
{
	float				xy[4];
	int					usable;
	struct s_poslist	*next;
}						t_poslist;

typedef struct			s_tetlist
{
	char				**tetromino;
	struct s_poslist	*positions;
	struct s_tetlist	*next;
}						t_tetlist;

int						print_error(void);
int						print_usage(void);
void					exit_error(void);
void					validate_tetromino(char **array);
int						read_file(int fd, t_tetlist **tetrominos);

#endif
