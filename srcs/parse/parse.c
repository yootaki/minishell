#include "../../includes/parse.h"
#include <stdbool.h>

bool	is_next_redirect(t_token *tokens)
{
	if (tokens->next->type == CHAR_GREATER)
		return (true);
	if (tokens->next->type == CHAR_LESSER)
		return (true);
	if (tokens->next->type == HEAR_DOC)
		return (true);
	if (tokens->next->type == DGREATER)
		return (true);
	return (false);
}

int	is_type_pipe(t_nlst **n_lst, t_token **tokens)
{
	//printf("----is_type_pipe_START-----\n");
	//printf("str = %s\n", (*tokens)->str);
	if ((*tokens)->type == CHAR_PIPE)
	{
		//printf("----is_type_pipe-----\n");
		*n_lst = (*n_lst)->next;
		*tokens = (*tokens)->next;
		if (*tokens == NULL)
		{
			//printf("------is_type_pipe_if-----\n");
			return (EXIT_FAILURE);
		}
	}
	//printf("----is_type_pipe_END-----\n\n");
	return (EXIT_SUCCESS);
}

int	create_lst(t_nlst **n_lst, t_token **tokens)
{
	//printf("------------create_lst----------\n");
	//printf("tokens->str = %s\n", (*tokens)->str);
	//printf("tokens->type = %d\n", (*tokens)->type);
	if ((*tokens)->specified_fd == 1 || (*tokens)->type == CHAR_GREATER || (*tokens)->type == CHAR_LESSER \
	||(*tokens)->type == HEAR_DOC || (*tokens)->type == DGREATER)
	{
		if (create_redirect_lst((*n_lst)->redirect, tokens) == EXIT_FAILURE || (*tokens) == NULL)
			return (EXIT_FAILURE);
		//*tokens = (*tokens)->next;
	}
	else
	{
		if (create_cmd_lst((*n_lst)->cmd, *tokens) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	//printf("------------create_lst_end----------\n");
	return (EXIT_SUCCESS);
}

int	syntax_analysis(t_nlst *node, t_token *tokens)
{
	t_nlst	*current;

	current = node->next;
	while (current != node)
	{
		//printf("tokens->str = %s\n", tokens->str);
		if (is_type_pipe(&current, &tokens) == EXIT_FAILURE)
			break ;
		if (create_lst(&current, &tokens) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (tokens == NULL || tokens->next == NULL)
		{
			//printf("------break-----\n");
			break;
		}
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
	int	result = 0;

	//printf("-----parse_start-------\n");
	result = parse_separator(node, tokens, envp_lst);
	if (result == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//printf("-----parse_end-------\n");
	return (result);
}
