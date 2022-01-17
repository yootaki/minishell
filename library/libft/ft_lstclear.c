/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:52:44 by hryuuta           #+#    #+#             */
/*   Updated: 2021/09/15 17:02:11 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ndlst;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		ndlst = (*lst)->next;
		(*del)((*lst)->content);
		free((*lst));
		*lst = ndlst;
	}
}
