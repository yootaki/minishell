/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 03:35:15 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/14 03:35:16 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

void	ft_free(char **line, char **rest)
{
	free(*line);
	*line = NULL;
	free(*rest);
	*rest = NULL;
}

int	ft_get_line(int flag, char **line, char **rest, char *buf)
{
	char		*end;
	char		*tmp;

	if (!*line)
		*line = ft_strjoin_gnl("", buf);
	else
	{
		tmp = ft_strjoin_gnl(*line, buf);
		free(*line);
		*line = tmp;
	}
	tmp = NULL;
	end = ft_strchr_gnl(*line, '\n');
	if (end != NULL)
	{
		*end = '\0';
		while (*buf != '\n')
			buf++;
		buf++;
		tmp = ft_strdup_gnl(buf);
		flag = 1;
	}
	free(*rest);
	*rest = tmp;
	return (flag);
}

int	ft_read(int flag, int *fd, char **line, char **rest)
{
	ssize_t		rd;
	char		*buf;

	if (flag != 0)
		return (flag);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (-1);
	while (flag == 0)
	{
		rd = read(*fd, buf, BUFFER_SIZE);
		if (!(rd > 0))
			break ;
		buf[rd] = '\0';
		flag = ft_get_line(flag, line, rest, buf);
	}
	if (rd < 0)
		flag = -1;
	free(buf);
	buf = NULL;
	return (flag);
}

int	get_next_line(int fd, char **line)
{
	int			flag;
	static char	*rest;

	flag = 0;
	if (fd < 0)
		return (-1);
	*line = ft_strdup_gnl("\0");
	if (rest)
		flag = ft_get_line(flag, line, &rest, rest);
	flag = ft_read(flag, &fd, line, &rest);
	if (flag == -1)
		ft_free(line, &rest);
	return (flag);
}
