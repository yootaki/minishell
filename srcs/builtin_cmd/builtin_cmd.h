#ifndef BUILTIN_CMD_H
#define BUILTIN_CMD_H

#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

typedef struct	s_envlist
{
	struct s_envlist	*prev;
	struct s_envlist	*next;
	char				*key;
	char				*value;
}t_envlist;

t_envlist	*ft_envlstnew(char *key, char *value);
void		ft_envlstdelone(t_envlist *lst);
void		ft_envlstadd_back(t_envlist *top, t_envlist *new);
int			ft_envlstsize(t_envlist *lst);
void		free_envlst(t_envlist *lst);

#endif
