/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_free_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:49 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/05 14:03:50 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	ft_exit(int status)
{
	g_status = status;
	exit(g_status);
}

void	free_path_list(char **path_list)
{
	int	i;

	i = 0;
	if (path_list == NULL)
		return ;
	while (path_list[i] != NULL)
	{
		free(path_list[i]);
		i++;
	}
	free(path_list);
	path_list = NULL;
}

void	free_function(t_data *data, int pattern)
{
	if (pattern == 1)
	{
		free_node(data->top);
	}
	if (pattern == 2)
	{
		free_path_list(data->path_list);
		free_node(data->top);
	}
	if (pattern == 3)
	{
		free(data->cmd);
		data->cmd = NULL;
		free_path_list(data->path_list);
		free_node(data->top);
	}
	exit(EXIT_FAILURE);
}
