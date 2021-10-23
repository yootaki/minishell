/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:46 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/23 20:47:02 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expansion.h"

int	cmd_lst_len(t_cmd_lst *cmd)
{
	t_cmd_lst	*current;
	int			i;

	i = 0;
	current = cmd->next;
	while (current != cmd)
	{
		current = current->next;
		i++;
	}
	return (i);
}

char	**get_cmd_str(t_nlst *node)
{
	t_cmd_lst	*current;
	int			i;
	char		**cmd_array;

	cmd_array = (char **)malloc(sizeof(char *) * (cmd_lst_len(node->cmd) + 1));
	if (!cmd_array)
		exit (print_error_func("malloc"));
	current = node->cmd->next;
	i = 0;
	while (current != node->cmd)
	{
		cmd_array[i] = current->str;
		current = current->next;
		i++;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
}

char	**create_cmd_array(t_nlst *node, t_data *data)
{
	char	*tmp_cmd;

	get_path(node, data);
	data->cmd = get_cmd_str(node);
	if (data->cmd == NULL)
		free_function(data, 2);
	tmp_cmd = search_cmd(data->cmd[0], data);
	if (tmp_cmd == NULL)
		free_function(data, 3);
	data->cmd[0] = tmp_cmd;
	return (data->cmd);
}
