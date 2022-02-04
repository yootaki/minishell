/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:04:13 by hryuuta           #+#    #+#             */
/*   Updated: 2022/02/04 16:24:34 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**search_path(t_envlist	*envp)
{
	t_envlist	*current;
	char		**path;

	current = envp->next;
	while (ft_strncmp(current->key, "PATH", 4) != 0 && current != envp)
	{
		printf("---------a-----------\n");
		printf("current->key = %s\n", current->key);
		printf("current->value = %s\n", current->value);
		printf("--------------------\n");
		current = current->next;
	}
	printf("--------------------\n");
	printf("--------------------\n");
	if (current == envp)
		return (NULL);
	printf("--------------------\n");
	path = ft_xsplit(current->value, ':');
	printf("--------------------\n");
	return (path);
}

int	get_path(t_nlst *node, t_data *data)
{
	printf("-----------get_path---------\n");
	data->path_list = search_path(node->envp_lst);
	//data->path_list = NULL;
	printf("-----------get_path---------\n");
	/* if (data->path_list == NULL)
		free_function(data, 1); */
	printf("get_path\n");
	return (EXIT_SUCCESS);
}
