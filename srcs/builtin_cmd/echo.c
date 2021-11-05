/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:42:21 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/05 13:28:12 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

int	check_option(char *str)
{
	if (str == NULL)
		return (1);
	if (*str == '-')
		str++;
	if (*str == '\0')
		return (1);
	while (*str == 'n' && *str != '\0')
		str++;
	if (*str == '\0')
		return (0);
	return (1);
}

void	print_args(t_cmd_lst *now, t_cmd_lst *cmd)
{
	while (now != cmd)
	{
		ft_putstr_fd (now->str, STDOUT_FILENO);
		now = now->next;
		if (now != cmd)
			write(STDOUT_FILENO, " ", 1);
	}
}

int	my_echo(t_cmd_lst *cmd)
{
	t_cmd_lst	*now;
	int			display_return;

	now = cmd->next->next;
	display_return = 1;
	if (now == cmd)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	while (now != cmd && !check_option(now->str))
	{
		display_return = 0;
		now = now->next;
	}
	print_args(now, cmd);
	if (display_return)
		write(STDOUT_FILENO, "\n", 1);
	if (STDOUT_FILENO > 2)
		close(STDOUT_FILENO);
	g_status = 0;
	return (EXIT_SUCCESS);
}
