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

#include "../../includes/expansion.h"
#include "builtin_cmd.h"

#define VALID_IDENTIFIER "minishell: export: not valid in this context: \n"

bool	validate_args(char *arg)
{
	if (arg == NULL)
	{
		return (false);
	}
	else if (arg[0] == '=' || arg[0] == ' ' || ft_isdigit(arg[0]))
	{
		return (false);
	}
	return (true);
}

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
		if (!validate_args(now->str))
		{
			ft_putstr_fd(VALID_IDENTIFIER, STDERR_FILENO);
			g_status = 1;
			break;
		}
		else if (insert_key_and_value(now, envp_lst) == 1)
		{
			g_status = 1;
			break ;
		}
		now = now->next;
	}
	return (g_status);
}
