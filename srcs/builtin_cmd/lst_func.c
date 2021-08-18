#include "builtin_cmd.h"

t_envlist	*ft_envlstnew(char *key, char *value)
{
	t_envlist	*lst;

	lst = (t_envlist *)malloc(sizeof(t_envlist));
	if (lst == NULL)
		return (NULL);
	lst->prev = lst;
	lst->next = lst;
	lst->key = key;
	lst->value = value;
	return (lst);
}

void	ft_envlstdelone(t_envlist *lst)
{
	t_envlist	*prev;
	t_envlist	*next;

	prev = lst->prev;
	next = lst->next;
	prev->next = next;
	next->prev = prev;
	free(lst);
}

void	ft_envlstadd_back(t_envlist *top, t_envlist *new)
{
	t_envlist	*last;

	if (top == NULL || new == NULL)
		return ;
	last = top->prev;
	top->prev = new;
	last->next = new;
	new->prev = last;
	new->next = top;
}

int	ft_envlstsize(t_envlist *lst)
{
	int			count;
	t_envlist	*sentinel;

	if (lst == NULL)
		return (0);
	count = 0;
	sentinel = lst;
	lst = lst->next;
	while (lst != sentinel)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	free_envlst(t_envlist *lst)
{
	t_envlist	*tmp;
	int			n;

	n = ft_envlstsize(lst);
	while (n-- >= 0)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}
