/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:36 by hryuuta           #+#    #+#             */
/*   Updated: 2022/02/21 14:26:52 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*xmalloc(size_t size)
{
	void	*tmp;

	tmp = malloc(size);
	if (tmp == NULL)
	{
		ft_perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_memset(tmp, 0, size);
	return (tmp);
}

int	ft_open(char *pathname, int flags, mode_t mode)
{
	int	fd;

	if (mode == 0)
		fd = open(pathname, flags);
	else
		fd = open(pathname, flags, mode);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(pathname, STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	return (fd);
}

void	xwaitpid(pid_t pid, int *wstatus, int options)
{
	if (waitpid(pid, wstatus, options) == -1)
	{
		ft_perror("waitpid");
		exit(EXIT_FAILURE);
	}
}

void	ft_perror(char *error_str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(error_str);
}
