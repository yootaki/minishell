#ifndef UTILS_H
#define UTILS_H

#include "../libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdbool.h>

typedef struct	s_envlist
{
	struct s_envlist	*prev;
	struct s_envlist	*next;
	char				*key;
	char				*value;
}		t_envlist;

/* ./utils/envp_lst.c */
t_envlist	*init_envlist(void);
t_envlist	*ft_envlstnew(char *key, char *value);
void		ft_init_envlst(t_envlist *lst);
void		ft_envlstadd_back(t_envlist *top, t_envlist *new_lst);
int			ft_envlstsize(t_envlist *lst);
void		free_envplist(t_envlist *nil);

/* ./utils/get_envp.c */
int		envp_lstmap(t_envlist *envp, char *key, char *value);
int		create_envlst(t_envlist *lst, char **envp);
t_envlist	*get_envp(char **envp);

#endif
