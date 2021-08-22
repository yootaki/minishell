#include "parse.h"
#include <stdbool.h>

void	check_lst(t_nlst *nil)
{
	t_nlst	*current;
	t_cmd_lst *c_tmp;
	t_redirect	*r_tmp;

	current = nil->next;
	while (current != nil)
	{
		int i = 0;
		c_tmp = current->cmd->next;
		while (c_tmp != current->cmd)
		{
			c_tmp = c_tmp->next;
			i++;
		}
		i = 0;
		r_tmp = current->redirect->next;
		while (r_tmp != current->redirect)
		{
			r_tmp = r_tmp->next;
			i++;
		}
		current = current->next;
	}
}

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

int	create_cmd_lst(t_cmd_lst *cmd, t_token *tokens)
{
	if (cmd_lst_add(cmd, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_redirect_lst(t_redirect *redirect, t_token *tokens)
{
	if (redirect_lst_add(redirect, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	tokens = tokens->next;
	if (redirect_lst_add(redirect, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_node_lst(t_nlst *node, t_token *tokens)
{
	if (nlst_add(node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	int i = 0;
	while (1)
	{
		if (tokens->type == CHAR_PIPE)
		{
			if (tokens->next != NULL && tokens->next->type == CHAR_PIPE)
				return (EXIT_FAILURE);
			if (nlst_add(node) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		if (tokens->next == NULL)
			break;
		tokens = tokens->next;
		i++;
	}
	return (EXIT_SUCCESS);
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

int	parse_separator(t_nlst *node, t_token *tokens)
{
	if (create_node_lst(node, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (syntax＿analysis(node, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse(t_nlst *node, t_token *tokens)
{
	int	result = 0;

	result = parse_separator(node, tokens);
	check_lst(node);
	if (result == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (result);
}