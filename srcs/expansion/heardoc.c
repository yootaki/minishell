/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 23:04:30 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/26 20:18:26 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"
#include "../../includes/utils.h"

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
	var_value = ft_xstrdup(get_var_value(var_name, env));
	if (!var_value)
	{
		free(var_name);
		return (ft_xstrdup("\0"));
	}
	tmp = ft_xstrjoin(line, var_value);
	newline = ft_xstrjoin(tmp, &line[line_cnt + ft_strlen(var_name) + 1]);
	free(var_name);
	free(var_value);
	free(tmp);
	return (newline);
}

void	read_and_expansion_line(t_envlist *env, char *separator, int *pipe_fd)
{
	char	*expanded_line;
	char	*line;

	close(pipe_fd[READ]);
	while (1)
	{
		heardoc_signal_proc();
		line = readline("> ");
		if (line == NULL)
			return ;
		if (!ft_strncmp(line, separator, ft_strlen(separator) + 1))
			break ;
		expanded_line = heardoc_expansion_var(line, env);
		ft_putendl_fd(expanded_line, pipe_fd[WRITE]);
		free(line);
	}
	free(line);
}

int	write_to_stdout_from_stdin(t_envlist *env, char *separator, int *pipe_fd)
{
	pid_t	pid;
	pid_t	wait_pid;
	int		status;

	status = 0;
	pid = xfork();
	if (pid == -1)
		return (print_error_func("fork"));
	else if (pid == 0)
	{
		read_and_expansion_line(env, separator, pipe_fd);
		close(pipe_fd[WRITE]);
		exit (EXIT_SUCCESS);
	}
	else
		wait_pid = wait(&status);
	if (wait_pid == -1)
		return (print_error_func("wait"));
	return (EXIT_SUCCESS);
}

int	hear_doc(t_redirect *now, t_envlist *env, char *separator)
{
	int		pipe_fd[FD_NUM];

	if (pipe(pipe_fd) == -1)
		return (print_error_func("pipe"));
	if (now->prev->c_type == T_LESSER)
	{
		ft_putstr_fd(now->str, pipe_fd[WRITE]);
		ft_putstr_fd("\n", pipe_fd[WRITE]);
		close(pipe_fd[WRITE]);
		now->heardoc_fd = pipe_fd[READ];
		return (EXIT_SUCCESS);
	}
	if (write_to_stdout_from_stdin(env, separator, pipe_fd))
	{
		close(pipe_fd[WRITE]);
		return (EXIT_FAILURE);
	}
	close(pipe_fd[WRITE]);
	now->heardoc_fd = pipe_fd[READ];
	return (EXIT_SUCCESS);
}
