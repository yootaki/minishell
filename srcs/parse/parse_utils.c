/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 02:21:33 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/14 02:22:15 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include <stdbool.h>

bool	is_next_redirect(t_token_type type, int specified_fd)
{
	if (specified_fd == 1)
		return (true);
	if (type == CHAR_GREATER)
		return (true);
	if (type == CHAR_LESSER)
		return (true);
	if (type == HEAR_DOC)
		return (true);
	if (type == DGREATER)
		return (true);
	if (type == T_LESSER)
		return (true);
	return (false);
}

int	is_type_pipe(t_nlst **n_lst, t_token **tokens)
{
	if ((*tokens)->type == CHAR_PIPE)
	{
		*n_lst = (*n_lst)->next;
		*tokens = (*tokens)->next;
		if (*tokens == NULL)
		{
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
