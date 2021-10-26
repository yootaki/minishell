/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:02:39 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/26 13:07:03 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	create_redirect_lst(t_redirect *redirect, t_token **tokens)
{
	redirect_lst_add(redirect, *tokens);
	if ((*tokens)->specified_fd != 1)
	{
		if ((*tokens)->next == NULL)
				return (EXIT_SUCCESS);
		if (is_next_redirect((*tokens)->next->type, 0))
			return (EXIT_SUCCESS);
		else
		{
			*tokens = (*tokens)->next;
			redirect_lst_add(redirect, *tokens);
		}
	}
	return (EXIT_SUCCESS);
}

int	type_pipe(t_nlst *node, t_token *tokens, t_envlist *env)
{
	if (tokens->next != NULL && tokens->next->type == CHAR_PIPE)
	{
		ft_putendl_fd("bash: \
		syntax error near unexpected token `|'", 2);
		g_status = 258;
		return (EXIT_FAILURE);
	}
	nlst_add(node, env);
	return (EXIT_SUCCESS);
}

int	create_node_lst(t_nlst *node, t_token *tokens, t_envlist *env)
{
	nlst_add(node, env);
	if (tokens->type == CHAR_PIPE)
	{
		ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
		g_status = 258;
		return (EXIT_FAILURE);
	}
	while (1)
	{
		if (tokens->type == CHAR_PIPE)
			if (type_pipe(node, tokens, env) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		if (tokens->next == NULL)
			break ;
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
