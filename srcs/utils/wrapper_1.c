/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:17:08 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/05 14:02:52 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "expansion.h"

void	xclose(int fd)
{
	if (0 <= fd && close(fd) == -1)
	{
		if (errno != EBADF)
		{
			ft_perror("close");
			exit(EXIT_FAILURE);
		}
	}
}

int	xdup2(int oldfd, int newfd)
{
	int	fd;

	fd = 0;
	if (oldfd < 0)
		return (-1);
	if (oldfd != newfd)
	{
		fd = dup2(oldfd, newfd);
		if (fd == -1)
		{
			ft_putstr_fd("dup2 : ", STDERR_FILENO);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		}
		xclose(oldfd);
	}
	return (fd);
}

int	xdup(int oldfd, int *stdfd)
{
	int	newfd;

	newfd = dup(oldfd);
	if (newfd == -1)
	{
		ft_putstr_fd("dup : ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
		*stdfd = newfd;
	return (newfd);
}

int	xpipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		ft_perror("pipe");
		pipefd[0] = -1;
		pipefd[1] = -1;
		return (-1);
	}
	return (0);
}

pid_t	xfork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}
