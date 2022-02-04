/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:08 by hryuuta           #+#    #+#             */
/*   Updated: 2022/02/03 20:05:21 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "expansion.h"

t_envlist	*init_envlist(void)
{
	t_envlist	*nil;

	nil = (t_envlist *)xmalloc(sizeof(t_envlist));
	nil->next = nil;
	nil->prev = nil;
	nil->key = NULL;
	nil->value = NULL;
	return (nil);
}

t_envlist	*ft_envlstnew(char *key, char *value)
{
	t_envlist	*lst;

	lst = (t_envlist *)xmalloc(sizeof(t_envlist));
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

void	ft_envlstdelone(t_envlist *lst)
{
	t_envlist	*prev;
	t_envlist	*next;

	prev = lst->prev;
	next = lst->next;
	prev->next = next;
	next->prev = prev;
	free(lst);
	lst = NULL;
}
