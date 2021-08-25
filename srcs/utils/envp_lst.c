#include "utils.h"

t_envlist	*init_envlist(void)
{
	t_envlist	*nil;

	nil = (t_envlist *)malloc(sizeof(t_envlist));
	if (!nil)
		return (NULL);
	nil->next = nil;
	nil->prev = nil;
	nil->key = NULL;
	nil->value = NULL;
	return (nil);
}

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

void	ft_envlstadd_back(t_envlist *top, t_envlist *new_lst)
{
	t_envlist	*last;

	if (top == NULL || new_lst == NULL)
		return ;
	last = top->prev;
	top->prev = new_lst;
	last->next = new_lst;
	new_lst->prev = last;
	new_lst->next = top;
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

void	free_envplist(t_envlist *nil)
{
	t_envlist	*current;
	t_envlist	*tmp;

	current = nil->next;
	while (current != nil)
	{
		free(current->key);
		free(current->value);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	free(nil);
}
