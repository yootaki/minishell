/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:04:13 by hryuuta           #+#    #+#             */
/*   Updated: 2022/02/19 13:25:15 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**search_path(t_envlist	*envp)
{
	t_envlist	*current;
	char		**path;

	if (envp == NULL)
		return (NULL);
	current = envp->next;
	while (current != envp && ft_strncmp(current->key, "PATH", 4) != 0)
		current = current->next;
	if (current == envp)
		return (NULL);
	path = ft_xsplit(current->value, ':');
	return (path);
}

int	get_path(t_nlst *node, t_data *data)
{
	data->path_list = search_path(node->envp_lst);
	return (EXIT_SUCCESS);
}
