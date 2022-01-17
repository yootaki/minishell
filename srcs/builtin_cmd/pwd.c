/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:42:56 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/05 13:29:59 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

int	my_pwd(t_envlist *envp_lst)
{
	t_envlist	*tmp;

	tmp = envp_lst->next;
	while (ft_strncmp(tmp->key, "PWD", 4) && tmp != envp_lst)
		tmp = tmp->next;
	printf("%s\n", tmp->value);
	return (EXIT_SUCCESS);
}
