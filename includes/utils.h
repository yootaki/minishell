#ifndef UTILS_H
#define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdbool.h>
# include "libft.h"

typedef struct	s_envlist
{
	struct s_envlist	*prev;
	struct s_envlist	*next;
	char				*key;
	char				*value;
}		t_envlist;

/* ./utils/envp_lst.c */
t_envlist	*init_dlist();
t_envlist	*ft_envlstnew(char *key, char *value);
void		ft_init_envlst(t_envlist *lst);
void		ft_envlstadd_back(t_envlist *top, t_envlist *new_lst);
int			ft_envlstsize(t_envlist *lst);
void		lst_free(t_envlist *lst);
int		get_envp(char **envp);
#endif
