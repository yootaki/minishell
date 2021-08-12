/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:52:44 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/21 04:33:53 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear (t_list **lst, void (*del)(void*))
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
