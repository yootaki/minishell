/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_next_cmd_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:04:59 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/23 20:55:03 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expansion.h"

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

	new_node = xget_cmdline_from_input_str(p_line, envp_lst);
	if (expansion(new_node, envp_lst) == EXIT_FAILURE)
	{
		free_node(new_node);
		return (EXIT_FAILURE);
	}
	current = new_node->next;
	while (current != new_node)
	{
		tmp_lst = current->next;
		nlst_bottom_add(n_lst, current);
		current = tmp_lst;
	}
	free(new_node);
	return (EXIT_SUCCESS);
}

int	add_pipe_next_cmd(char **p_line)
{
	int		status;
	char	*line;

	heardoc_signal_proc();
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
			break ;
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
	char		*p_line;
	static int	i;

	i++;
	r_now = node->redirect->next;
	c_now = node->cmd->next;
	p_line = NULL;
	if (!r_now->str && !c_now->str)
	{
		delete_node(n_lst, node);
		if (add_pipe_next_cmd(&p_line) == EXIT_FAILURE)
			return (FAILURE);
		if (add_new_node_lst(n_lst, envp_lst, p_line) == EXIT_FAILURE)
		{
			free_node(n_lst);
			return (FAILURE);
		}
		free(p_line);
		return (SKIP);
	}
	return (SUCCESS);
}
