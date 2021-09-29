/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:42:21 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/29 23:50:11 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

int	get_redirect_fd(t_redirect *redirect)
{
	t_redirect	*now;
	int			fd;

	fd = STDOUT_FILENO;
	now = redirect->next;
	while (now != redirect)
	{
		if ((!ft_strncmp(now->str, ">", ft_strlen(now->str) + 1) \
		|| !ft_strncmp(now->str, ">>", ft_strlen(now->str) + 1)) \
		&& now->next->redirect_fd > 2)
		{
			now = now->next;
			fd = now->redirect_fd;
		}
		now = now->next;
	}
	return (fd);
}

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

void	print_args(t_cmd_lst *now, t_cmd_lst *cmd, int redirect_fd)
{
	while (now != cmd)
	{
		ft_putstr_fd (now->str, redirect_fd);
		now = now->next;
		if (now != cmd)
			write(redirect_fd, " ", 1);
	}
}

int	my_echo(t_cmd_lst *cmd, t_redirect *redirect)
{
	t_cmd_lst	*now;
	int			display_return;
	int			redirect_fd;

	now = cmd->next->next;
	redirect_fd = get_redirect_fd(redirect);
	display_return = 1;
	if (now == cmd)
	{
		write(redirect_fd, "\n", 1);
		return (EXIT_SUCCESS);
	}
	while (now != cmd && !check_option(now->str))
	{
		display_return = 0;
		now = now->next;
	}
	print_args(now, cmd, redirect_fd);
	if (display_return)
		write(redirect_fd, "\n", 1);
	if (redirect_fd > 2)
		close(redirect_fd);
	g_status = 0;
	return (EXIT_SUCCESS);
}
