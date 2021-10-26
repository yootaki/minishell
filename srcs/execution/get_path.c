/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:04:13 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/26 16:33:12 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

char	**search_path(t_envlist	*envp)
{
	t_envlist	*current;
	char		**path;

	current = envp->next;
	while (ft_strncmp(current->key, "PATH", 4) != 0 && current != envp)
		current = current->next;
	if (current == envp)
		return (NULL);
	path = ft_xsplit(current->value, ':');
	return (path);
}

int	get_path(t_nlst *node, t_data *data)
{
	data->path_list = search_path(node->envp_lst);
	if (data->path_list == NULL)
		free_function(data, 1);
	return (EXIT_SUCCESS);
}
