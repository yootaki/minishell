/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:42:40 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/11 21:15:29y yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"
#include "../../libft/libft.h"
#include "../../includes/expansion.h"
#include "../../includes/utils.h"

#define VALID_IDENTIFIER "minishell: export: `': not a valid identifier\n"

int	my_export(t_cmd_lst *cmd, t_envlist *envp_lst)
{
	t_cmd_lst	*now;

	now = cmd->next->next;
	g_status = 0;
	if (now == cmd)
	{
		sort_and_print_env(envp_lst);
		return (g_status);
	}
	while (now != cmd)
	{
		if (now->str == NULL || ft_isdigit(now->str[0]))
		{
			ft_putstr_fd(VALID_IDENTIFIER, STDERR_FILENO);
			g_status = 1;
		}
		else if (insert_key_and_value(now, envp_lst))
		{
			g_status = 1;
			break ;
		}
		now = now->next;
	}
	return (g_status);
}
