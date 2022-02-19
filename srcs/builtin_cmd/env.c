/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:42:26 by yootaki           #+#    #+#             */
/*   Updated: 2022/02/19 14:19:54 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

int	my_env(t_envlist *envp_lst)
{
	t_envlist	*tmp;

	if (envp_lst == NULL)
		return (EXIT_SUCCESS);
	tmp = envp_lst->next;
	while (tmp != envp_lst)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
