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
		printf("-----------\n");
		int i = 0;
		c_tmp = current->cmd->next;
		while (c_tmp != current->cmd)
		{
			printf("cmd_str[%d] = %s\n", i, current->cmd->str);
			current->cmd = current->cmd->next;
			i++;
		}
		i = 0;
		r_tmp = current->redirect->next;
		while (r_tmp != current->redirect)
		{
			printf("redirect_str[%d] = %s\n", i, current->redirect->str);
			current->redirect = current->redirect->next;
			i++;
		}
		current = current->next;
	}
}

bool	is_next_redirect(t_token *tokens)
{
	printf("tokens->type = %d\n", tokens->next->type);
	if (tokens->next->type == CHAR_GREATER)
		return (true);
	if (tokens->next->type == CHAR_LESSER)
		return (true);
	if (tokens->next->type == HEAR_DOC)
		return (true);
	if (tokens->next->type == DLESSER)
		return (true);
	printf("-----is_next_redirect_end----\n");
	return (false);
}

int	create_cmd_lst(t_cmd_lst *cmd, t_token *tokens)
{
	printf("-------create_cmd_lst_start------\n");
	printf("------1---\n");
	printf("tokens->str = %s\n", tokens->str);
	printf("tokens->type = %d\n", tokens->type);
	if (cmd_lst_add(cmd, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_redirect_lst(t_redirect *redirect, t_token *tokens)
{
	printf("-------create_redirect_lst_start------\n");
	printf("------1---\n");
	printf("tokens->str = %s\n", tokens->str);
	printf("tokens->type = %d\n", tokens->type);
	if (redirect_lst_add(redirect, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	tokens = tokens->next;
	if (redirect_lst_add(redirect, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("-------create_redirect_lst_end------\n");
	return (EXIT_SUCCESS);
}

int	create_node_lst(t_nlst **node, t_token *tokens)
{
	if (nlst_add(*node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	int i = 0;
	while (1)
	{
		printf("[%d]\n", i);
		if (tokens->type == CHAR_PIPE)
		{
			printf("------if-------\n");
			if (tokens->next != NULL && tokens->next->type == CHAR_PIPE)
				return (EXIT_FAILURE);
			if (nlst_add(*node) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		if (tokens->next == NULL)
			break;
		tokens = tokens->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	syntax＿analysis(t_nlst **node, t_token *tokens)
{
	t_nlst	*current;
	t_nlst	*top;

	top = *node;
	current = (*node)->next;
	*node = (*node)->next;
	while (current != *node)
	{
		if (tokens->type == CHAR_PIPE)
		{
			*node = (*node)->next;
			current = current->next;
			tokens = tokens->next;
		}
		printf("-----loop_start-----\n");
		printf("tokens = %s\n", tokens->str);
		printf("tokne_type = %d\n", tokens->type);
		if (tokens->type == CHAR_GREATER || tokens->type == CHAR_LESSER \
		||tokens->type == HEAR_DOC || tokens->type == DLESSER)
		{
			printf("-----else-if--------\n");
			if (create_redirect_lst((*node)->redirect, tokens) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			tokens = tokens->next;
		}
		else
		{
			printf("------else-------\n");
			if (create_cmd_lst((*node)->cmd, tokens) == EXIT_FAILURE)
				return (EXIT_FAILURE);	
		}
		if (tokens->next == NULL)
		{
			*node = top;
			break;
		}	
		tokens = tokens->next;
	}
	check_lst(*node);
	printf("-------parse_separator_end------\n");
	return (EXIT_SUCCESS);
}

int	parse_separator(t_nlst **node, t_token *tokens)
{
	printf("-------parse_separator_start------\n");
	printf("CHAR_PIPE = %d\n", CHAR_PIPE);
	printf("CHAR_GREATER = %d\n", CHAR_GREATER);
	printf("CHAR_LESSER = %d\n", CHAR_LESSER);
	printf("HEAR_DOC = %d\n", HEAR_DOC);
	printf("DLESSER = %d\n", DLESSER);
	printf("DLESSER = %d\n", DLESSER);
	if (create_node_lst(node, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (syntax＿analysis(node, tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse(t_nlst **node, t_token *tokens)
{
	int	result = 0;

	printf("-------------\n");
	result = parse_separator(node, tokens);
	check_lst(*node);
	if (result == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (result);
}