/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:58 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/06 14:44:04 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	free_path_lst(t_data *data)
{
	int	i;

	i = 0;
	while (data->path_list[i] != NULL)
	{
		free(data->path_list[i]);
		i++;
	}
	free(data->path_list);
	data->path_list = NULL;
}

void	free_data_lst(t_data *data)
{
	free(data->cmd_array);
}

void	free_all(char **cmd_array, t_nlst *node, t_data *data)
{
	free(cmd_array);
	free_node(node);
	free_data_lst(data);
	exit(1);
}
