#ifndef BUILTIN_CMD_H
#define BUILTIN_CMD_H

typedef struct	s_envlist
{
	struct s_envlist	*prev;
	struct s_envlist	*next;
	char				*key;
	char				*value;
}t_envlist;

t_envlist	*ft_envlstnew(char *key, char *value);
void		ft_envlstadd_back(t_envlist *top, t_envlist *new);
int			ft_envlstsize(t_envlist *lst);
void		lst_free(t_envlist *lst);

#endif
