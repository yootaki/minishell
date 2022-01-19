/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:04:02 by hryuuta           #+#    #+#             */
/*   Updated: 2022/01/18 14:31:27 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	init_execution(t_data *data, t_nlst *node)
{
	data->cmd_array = NULL;
	data->path_list = NULL;
	data->cmd = NULL;
	data->top = node;
	data->backup_stdout = -1;
	data->backup_stdin = -1;
	data->backup_error = -1;
}

static int	cmd_type(char *str, int type)
{
	free(str);
	return (type);
}

int	is_builtin_cmd(char *cmd)
{
	char	*new_str;

	new_str = tolower_cmd(cmd);
	if (new_str == NULL)
		return (cmd_type(new_str, OTHER));
	else if (ft_strcmp(new_str, "echo") == 0)
		return (cmd_type(new_str, ECHO));
	else if (ft_strcmp(new_str, "cd") == 0)
		return (cmd_type(new_str, CD));
	else if (ft_strcmp(new_str, "env") == 0)
		return (cmd_type(new_str, ENV));
	else if (ft_strcmp(new_str, "export") == 0)
		return (cmd_type(new_str, EXPORT));
	else if (ft_strcmp(new_str, "pwd") == 0)
		return (cmd_type(new_str, PWD));
	else if (ft_strcmp(new_str, "unset") == 0)
		return (cmd_type(new_str, UNSET));
	else if (ft_strcmp(new_str, "exit") == 0)
		return (cmd_type(new_str, EXIT));
	else
		return (cmd_type(new_str, OTHER));
}
