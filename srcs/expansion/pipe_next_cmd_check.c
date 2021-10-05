/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_next_cmd_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:04:59 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/05 14:05:24 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expansion.h"

void	xcheck(t_nlst *nil)
{
	int i = 0;
	t_nlst		*current;
	t_cmd_lst	*c_tmp;
	t_redirect	*r_tmp;
	//printf("--------xcheck_START---------\n");
	//printf("nil_p = %p\n", nil);
	current = nil->next;
	while (current != nil)
	{
		i = 0;
		//printf("current_p = %p\n", current);
		c_tmp = current->cmd->next;
		//printf("current->cmd = %p\n", current->cmd);
		while (c_tmp != current->cmd)
		{
			//printf("c_str = %s\n", c_tmp->str);
			//printf("c_str_p = %p\n", c_tmp->str);
			//printf("c_type = %d\n", c_tmp->c_type);
			//printf("c_tmp_p = %p\n", c_tmp);
			c_tmp = c_tmp->next;
			i++;
		}
		i = 0;
		r_tmp = current->redirect->next;
		//printf("current->redirect = %p\n", current->redirect);
		while (r_tmp != current->redirect)
		{
			//printf("-----xcheck---\n");
			//printf("r_str = %s\n", r_tmp->str);
			//printf("r_str = %p\n", r_tmp->str);
			//printf("r_type = %d\n", r_tmp->c_type);
			//printf("r_tmp_p = %p\n", r_tmp);
			r_tmp = r_tmp->next;
			i++;
		}
		current = current->next;
	}
	//printf("--------xcheck_END---------\n");
//printf("---------end--------\n");
}

t_token_type	check_cmd_exist(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (CHAR_NULL);
	i = (int)(ft_strlen(line) - 1);
	if (i < 0)
		return (CHAR_NULL);
	while (i >= 0 && line[i] == CHAR_WHITESPACE)
		i--;
	if (i < 0)
		return (CHAR_WHITESPACE);
	if (line[i] == CHAR_PIPE)
		return (CHAR_PIPE);
	if (ft_isalnum(line[i]) == 1 || line[i] != CHAR_PIPE)
		return (CHAR_GENERAL);
	return (CHAR_GENERAL);
}

t_nlst	*xget_cmdline_from_input_str(char *command, t_envlist *envp_lst)
{
	t_nlst		*node;
	t_tokeniser	data;

	node = init_node();
	if (!node)
		return (NULL);
	lexer(&data, command);
	if (data.token == NULL)
		return (NULL);
	if (parse(node, data.token, envp_lst) == EXIT_FAILURE)
	{
		free_data(&data);
	 	free_node(node);
		return (NULL);
	}
	free_data(&data);
	return (node);
}

int	add_new_node_lst(t_nlst *n_lst, t_envlist *envp_lst, char *p_line)
{
	t_nlst		*new_node;
	t_nlst		*current;
	t_nlst		*tmp_lst;

	//printf("-------1-------\n");
	new_node = xget_cmdline_from_input_str(p_line, envp_lst);
	//printf("-------2-------\n");
	if (expansion(new_node, envp_lst) == EXIT_FAILURE)
	{
		free_node(new_node);
		return (EXIT_FAILURE);
	}
	//printf("-------3-------\n");
	current = new_node->next;
	//printf("---new_node_START-----\n");
	//xcheck(new_node);
	//printf("---new_node_END-----\n");
	//printf("-------4-------\n");
	while (current != new_node)
	{
		tmp_lst = current->next;
		nlst_bottom_add(n_lst, current);
		//printf("-------5-------\n");
		current = tmp_lst;
	}
	//printf("-------6-------\n");
	//free(new_node->cmd);
	//printf("-------7-------\n");
	//free(new_node->redirect);
	//printf("-------8-------\n");
	//xcheck(n_lst);
	free(new_node);
	//printf("-------9-------\n");
	return (EXIT_SUCCESS);
}

int	add_pipe_next_cmd(char **p_line)
{
	int		status;
	char	*line;

	redirect_signal_proc();
	while (1)
	{
		ft_putstr_fd("pipe > ", 1);
		status = get_next_line(0, &line);
		if (check_cmd_exist(line) == CHAR_GENERAL)
		{
			if (cmd_cmb(p_line, line) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			break ;
		}
		if (status == 0)
			break;
		if (cmd_cmb(p_line, line) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		free(line);
		if (status == -1)
			return (EXIT_FAILURE);
	}
	free(line);
	return (EXIT_SUCCESS);
}

t_flag	pipe_next_cmd_check(t_nlst *node, t_envlist *envp_lst, t_nlst *n_lst)
{
	t_redirect	*r_now;
	t_cmd_lst	*c_now;
	static int i;
	char	*p_line;

	i++;
	//printf("--pipe_next_cmd_check_START--[%d]回目\n\n", i);
	r_now = node->redirect->next;
	c_now = node->cmd->next;
	p_line = NULL;
	if (!r_now->str && !c_now->str)
	{
		//printf("-------exist_pipe------\n");
		delete_node(n_lst, node);
		if(add_pipe_next_cmd(&p_line) == EXIT_FAILURE)
			return (FAILURE);
		if(add_new_node_lst(n_lst, envp_lst, p_line) == EXIT_FAILURE)
		{
			free_node(n_lst);
			return (FAILURE);
		}
		free(p_line);
		return (SKIP);
	}
	//printf("--pipe_next_cmd_check_END--[%d]回目\n\n", i);
	return (SUCCESS);
}
