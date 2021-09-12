/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:42:21 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/10 14:05:18 by hryuuta          ###   ########.fr       */
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
	if (now->str == NULL)
	{
		write(redirect_fd, "\n", 1);
		return (EXIT_SUCCESS);
	}
	if (!ft_strncmp(now->str, "-n", ft_strlen(now->str)))
	{
		display_return = 0;
		now = now->next;
	}
	print_args(now, cmd, redirect_fd);
	if (display_return)
		write(redirect_fd, "\n", 1);
	if (redirect_fd > 2)
		close(redirect_fd);
	return (EXIT_SUCCESS);
}
