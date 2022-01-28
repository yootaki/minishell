/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:04:22 by hryuuta           #+#    #+#             */
/*   Updated: 2022/01/29 00:24:06 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_call_child(t_nlst *node, t_data *data, int prev_read_fd, int *pipefd)
{
	xdup2(prev_read_fd, STDIN_FILENO);
	xclose(pipefd[READ]);
	if (node->next != data->top \
	&& xdup2(pipefd[WRITE], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	xclose(pipefd[WRITE]);
	execute_command(node, data);
	exit(g_status);
}

int	ft_call_parent(t_nlst *node, t_data *data, int prev_read_fd, int *pipefd)
{
	xclose(pipefd[WRITE]);
	if (prev_read_fd != STDIN_FILENO)
		xclose(prev_read_fd);
	if (node->next == data->top)
		xclose(pipefd[READ]);
	return (pipefd[READ]);
}

/*
 * とりあえず、大まかな流れだけ書いてますので、エラー対応などは一切してません。
 */

int	execution_process(t_nlst *node, t_data *data)
{
	t_nlst	*current;
	int		pipefd[FD_NUM];
	int		pid;
	int		prev_read_fd;

	prev_read_fd = STDIN_FILENO;
	current = node->next;
	signal(SIGINT, SIG_IGN);
	while (current != node)
	{
		xpipe(pipefd);
		pid = xfork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			ft_call_child(current, data, prev_read_fd, pipefd);
		}
		else
			prev_read_fd = ft_call_parent(current, data, prev_read_fd, pipefd);
		free_data_lst(data);
		current = current->next;
	}
	return (pid);
}
