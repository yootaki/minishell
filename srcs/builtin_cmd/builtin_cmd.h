#ifndef BUILTIN_CMD_H
# define BUILTIN_CMD_H

# include "../../libft/libft.h"
# include "../../includes/input.h"
# include "../../includes/parse.h"
# include "../../includes/utils.h"
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

char		*malloc_and_copy(char *str, int size);

// t_envlist	*ft_envlstnew(char *key, char *value);
void		ft_envlstdelone(t_envlist *lst);
// void		ft_envlstadd_back(t_envlist *top, t_envlist *new);
// int			ft_envlstsize(t_envlist *lst);
void		free_envlst(t_envlist *lst);

#endif
