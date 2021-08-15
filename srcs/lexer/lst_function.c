#include "input.h"

t_token	*lst_new(char *str)
{
	t_token	*lst;

	lst = (t_token *)malloc(sizeof(t_token));
	if (lst == NULL)
		return (NULL);
	lst->str = str;
	lst->next = NULL;
	lst->type = 0;
	return (lst);
}

void	lst_clear (t_token **lst, void (*del)(char*))
{
	t_token	*ndlst;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		ndlst = (*lst)->next;
		(*del)((*lst)->str);
		free((*lst));
		*lst = ndlst;
	}
}

t_token	*lst_last(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_token **lst, t_token *new_list)
{
	t_token	*s;

	if (lst == NULL || new_list == NULL)
		return ;
	if (*lst == NULL)
		*lst = new_list;
	else
	{
		s = lst_last(*lst);
		if (s != NULL)
			s->next = new_list;
	}
}
