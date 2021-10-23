/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:17:08 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/23 18:36:07 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"
#include "../../includes/expansion.h"

void	xclose(int fd)
{
	if (close(fd) == -1)
	{
		ft_putstr_fd("close : ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

int	xdup2(int oldfd, int newfd)
{
	int	fd;

	fd = 0;
	if (oldfd != newfd)
	{
		fd = dup2(oldfd, newfd);
		if (fd == -1)
		{
			ft_putstr_fd("dup2 : ", STDERR_FILENO);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		xclose(oldfd);
	}
	else
		return (newfd);
	return (fd);
}

int	xdup(int oldfd)
{
	int	newfd;

	newfd = dup(oldfd);
	if (newfd == -1)
	{
		ft_putstr_fd("dup : ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (newfd);
}

void	xpipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
		exit(print_error_func("pipe"));
}

pid_t	xfork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(print_error_func("fork"));
	return (pid);
}
