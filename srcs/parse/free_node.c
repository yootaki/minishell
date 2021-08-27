#include "parse.h"

void	free_cmd_lst(t_cmd_lst *cmd)
{
	t_cmd_lst	*c_lst;
	t_cmd_lst	*c_tmp;

	c_lst = cmd->next;
	while (c_lst != cmd)
	{
		c_tmp = c_lst->next;
		free(c_lst);
		c_lst = NULL;
		c_lst = c_tmp;
	}
	free(c_lst);
	c_lst = NULL;
}

void	free_redirect_lst(t_redirect *redirect)
{
	t_redirect	*r_tmp;
	t_redirect	*r_lst;

	r_lst = redirect->next;
	while (r_lst != redirect)
	{
		r_tmp = r_lst->next;
		free(r_lst);
		r_lst = NULL;
		r_lst = r_tmp;
	}
	free(r_lst);
	r_lst = NULL;
}

void	free_node(t_nlst *node)
{
	t_nlst	*n_lst;
	t_nlst	*current;

	n_lst = node->next;
	while (n_lst != node)
	{
		current = n_lst->next;
		free_cmd_lst(n_lst->cmd);
		free_redirect_lst(n_lst->redirect);
		free(n_lst);
		n_lst = NULL;
		n_lst = current;
	}
	free(node);
}

void	free_data(t_tokeniser *data)
{
	t_token	*tlst;

	if (data->token == NULL)
		return ;
	while (data->token != NULL)
	{
		tlst = data->token->next;
		if (data->token->str != NULL)
			free(data->token->str);
		free(data->token);
		data->token = tlst;
	}
}
