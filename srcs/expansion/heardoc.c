/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 23:04:30 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/12 14:25:16 by yootaki          ###   ########.fr       */
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

//redirect_signal----------------------------------
void	redirect_sig_int_input()
{
	exit (EXIT_FAILURE);
}
void	redirect_sig_term_input()
{
}
void	redirect_sig_quit_input()
{
	ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
}

void	redirect_signal_proc()
{
	if (signal(SIGINT, redirect_sig_int_input) == SIG_ERR)
		perror("signal");
	else if (signal(SIGTERM, redirect_sig_term_input) == SIG_ERR)
		perror("signal");
	else if (signal(SIGQUIT, redirect_sig_quit_input) == SIG_ERR)
		perror("signal");
}
//----------------------------------------

void	read_and_expansion_line(t_envlist *env, char *separator, int *pipe_fd)
{
	char	*expanded_line;
	char	*line;
	int		status;

	redirect_signal_proc();
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
			exit (print_error_func("malloc"));
	}
	free(line);
}

int	hear_doc(t_redirect *now, t_envlist *env, char *separator)
{
	int		pipe_fd[FD_NUM];
	int		pid;
	int		wait_pid;
	int		status;

	status = 0;
	if (pipe(pipe_fd) == -1)
		return (print_error_func("pipe"));
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		read_and_expansion_line(env, separator, pipe_fd);
		exit (EXIT_SUCCESS);
	}
	else
		wait_pid = wait(&status);
	if (wait_pid == -1)
	{
		perror("wait");
		return (EXIT_FAILURE);
	}
	now->heardoc_fd = pipe_fd;
	return (EXIT_SUCCESS);
}
