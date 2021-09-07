/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 23:04:30 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/07 14:25:42 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

char	*heardoc_expansion_var(char *line, t_envlist *env)
{
	char	*var_name;
	char	*var_value;
	char	*newline;
	char	*tmp;
	int		line_cnt;

	line_cnt = 0;
	while (line[line_cnt] != '$' && line[line_cnt] != '\0')
		line_cnt++;
	if (line[line_cnt] == '\0')
		return (line);
	line[line_cnt] = '\0';
	var_name = get_var_name(&line[line_cnt + 1]);
	var_value = ft_strdup(get_var_value(var_name, env));
	tmp = ft_strjoin(line, var_value);
	newline = ft_strjoin(tmp, &line[line_cnt + ft_strlen(var_name) + 1]);
	free(var_name);
	free(var_value);
	free(tmp);
	return (newline);
}

static void	ft_putstr_endl(char *line, int *pipe_fd)
{
	ft_putstr_fd("> ", 1);
	ft_putendl_fd(line, pipe_fd[WRITE]);
}

int	hear_doc(t_redirect *now, t_envlist *env, char *separator)
{
	char	*expanded_line;
	char	*line;
	int		pipe_fd[FD_NUM];
	int		status;

	if (pipe(pipe_fd) == -1)
		return (print_error_func("pipe"));
	ft_putstr_fd("> ", 1);
	while (1)
	{
		status = get_next_line(0, &line);
		if (!ft_strncmp(line, separator, ft_strlen(separator) + 1))
			break ;
		expanded_line = heardoc_expansion_var(line, env);
		if (status == 1)
			ft_putstr_endl(expanded_line, pipe_fd);
		else if (status == 0)
			ft_putstr_fd(expanded_line, pipe_fd[WRITE]);
		free(line);
		if (status == -1)
			return (print_error_func("malloc"));
	}
	free(line);
	now->heardoc_fd = pipe_fd;
	return (EXIT_SUCCESS);
}
