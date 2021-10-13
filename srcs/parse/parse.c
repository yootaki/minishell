/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:01 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/14 02:22:42 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include <stdbool.h>

int	create_lst(t_nlst **n_lst, t_token **tokens)
{
	if (is_next_redirect((*tokens)->type, (*tokens)->specified_fd))
	{
		if (create_redirect_lst((*n_lst)->redirect, tokens) == EXIT_FAILURE \
		|| (*tokens) == NULL)
			return (EXIT_FAILURE);
	}
	else
	{
		if (create_cmd_lst((*n_lst)->cmd, *tokens) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	syntax_analysis(t_nlst *node, t_token *tokens)
{
	t_nlst	*current;

	current = node->next;
	while (current != node)
	{
		if (is_type_pipe(&current, &tokens) == EXIT_FAILURE)
			break ;
		if (create_lst(&current, &tokens) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (tokens == NULL || tokens->next == NULL)
			break ;
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}

int	parse_separator(t_nlst *node, t_token *tokens, t_envlist *env)
{
	if (create_node_lst(node, tokens, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (syntax_analysis(node, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse(t_nlst *node, t_token *tokens, t_envlist *envp_lst)
{
	int	result;

	result = 0;
	result = parse_separator(node, tokens, envp_lst);
	if (result == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (result);
}
