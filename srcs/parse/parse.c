#include "parse.h"
#include <stdbool.h>

bool	is_next_redirect(t_token *tokens)
{
	if (tokens->next->type == CHAR_GREATER)
		return (true);
	if (tokens->next->type == CHAR_LESSER)
		return (true);
	if (tokens->next->type == HEAR_DOC)
		return (true);
	if (tokens->next->type == DLESSER)
		return (true);
	return (false);
}

int	syntax＿analysis(t_nlst *node, t_token *tokens)
{
	t_nlst	*current;

	current = node->next;
	while (current != node)
	{
		if (tokens->type == CHAR_PIPE)
		{
			current = current->next;
			tokens = tokens->next;
		}
		if (tokens->type == CHAR_GREATER || tokens->type == CHAR_LESSER \
		||tokens->type == HEAR_DOC || tokens->type == DLESSER)
		{
			if (create_redirect_lst(current->redirect, tokens) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			tokens = tokens->next;
		}
		else
		{
			if (create_cmd_lst(current->cmd, tokens) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		if (tokens->next == NULL)
			break;
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}

int	parse_separator(t_nlst *node, t_token *tokens, t_envlist *env)
{
	if (create_node_lst(node, tokens, env) == EXIT_FAILURE)
	{
		free_lst(node);
		return (EXIT_FAILURE);
	}
	if (syntax＿analysis(node, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse(t_nlst *node, t_token *tokens, t_envlist *envp_lst)
{
	int	result = 0;

	result = parse_separator(node, tokens, envp_lst);
	if (result == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (result);
}
