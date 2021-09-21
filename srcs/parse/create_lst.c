#include "parse.h"

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
	if (tokens == NULL)
		return (EXIT_SUCCESS);
	if (redirect_lst_add(redirect, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_node_lst(t_nlst *node, t_token *tokens, t_envlist *env)
{
	if (nlst_add(node, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (tokens->type == CHAR_PIPE)
	{
		ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		if (tokens->type == CHAR_PIPE)
		{
			if (tokens->next != NULL && tokens->next->type == CHAR_PIPE)
			{
				ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
				return (EXIT_FAILURE);
			}
			if (nlst_add(node, env) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		if (tokens->next == NULL)
			break ;
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
