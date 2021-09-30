#include "parse.h"

void	free_cmd_lst(t_cmd_lst *cmd)
{
	t_cmd_lst	*c_lst;
	t_cmd_lst	*c_tmp;

	c_lst = cmd->next;
	//printf("c_lst->str = %s\n", c_lst->str);
	while (c_lst != cmd)
	{
		//printf("------------\n");
		c_tmp = c_lst->next;
		//printf("------free前--------\n");
		//printf("c_tmp->str = %s\n", c_tmp->str);
		//$ export TEST=test'で環境変数を追加したときにセグフォになったので一旦コメントアウトしています
		//printf("c_lst->str_p = %p\n", c_lst->str);
		//printf("c_lst->str = %s\n", c_lst->str);
		free(c_lst->str);
		c_lst->str = NULL;
		//printf("------free後--------\n");
		//printf("c_lst->str = %s\n", c_lst->str);
		//printf("c_tmp->str = %s\n", c_tmp->str)
		free(c_lst);
		c_lst = NULL;
		c_lst = c_tmp;
		//printf("c_lst->str = %s\n", c_lst->str);
		//printf("c_tmp->str = %s\n", c_tmp->str);
	}
	free(c_lst);
	c_lst = NULL;
}

void	free_redirect_lst(t_redirect *redirect)
{
	t_redirect	*r_tmp;
	t_redirect	*r_lst;

	//printf("---free_redirect_lst_START---\n");
	r_lst = redirect->next;
	while (r_lst != redirect)
	{
		r_tmp = r_lst->next;
		//printf("r_lst->str_p = %p\n", r_lst->str);
		//printf("r_lst->str = %s\n", r_lst->str);
		free(r_lst->str);
		r_lst->str = NULL;
		//printf("r_lst_p = %p\n", r_lst);
		free(r_lst);
		r_lst = NULL;
		r_lst = r_tmp;
	}
	free(r_lst);
	r_lst = NULL;
	//printf("---free_redirect_lst_END---\n");
}

void	free_node(t_nlst *node)
{
	t_nlst	*n_lst;
	t_nlst	*current;

	//printf("-------free_node_start-----\n");
	//printf("node_p = %p\n", node);
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
	//printf("-------free_node_end-----\n");
}

void	free_data(t_tokeniser *data)
{
	t_token	*tlst;

	if (data->token == NULL)
		return ;
	while (data->token != NULL)
	{
		tlst = data->token->next;
		//if (data->token->str != NULL)
			//free(data->token->str);
		//printf("data->token = %p\n",data->token);
		//printf("data->token_s = %s\n",data->token->str);
		if (data->token->type == CHAR_PIPE)
		{
			//printf("data->token->str_p = %p\n", data->token->str);
			free(data->token->str);
			data->token->str = NULL;
		}
		free(data->token);
		//printf("data->token = %p\n",data->token);
		data->token = NULL;
		data->token = tlst;
	}
}
