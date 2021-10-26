/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:02:31 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/26 16:28:34 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/input.h"
#include "../../includes/expansion.h"

t_token	*lst_new(char *str, int flag)
{
	t_token	*lst;

	lst = (t_token *)xmalloc(sizeof(t_token));
	lst->str = str;
	lst->next = NULL;
	lst->type = check_type(str);
	lst->specified_fd = flag;
	return (lst);
}

void	lst_clear(t_token **lst, void (*del)(void*))
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
