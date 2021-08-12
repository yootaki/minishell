/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:50:51 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/24 16:37:40 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_lst_sub;

	if (f == NULL)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		new_lst_sub = ft_lstnew((*f)(lst->content));
		if (new_lst_sub == NULL)
		{
			ft_lstclear(&new_lst, (*del));
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&new_lst, new_lst_sub);
	}
	return (new_lst);
}
