/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:04:06 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/05 13:37:20 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtin_cmd.h"

int	backup_std_fd(t_data *data, int mode)
{
	if (mode == STD_BACKUP)
	{
		if (xdup(STDIN_FILENO, &data->backup_stdin) == -1 \
		||xdup(STDOUT_FILENO, &data->backup_stdout) == -1 \
		||xdup(STDERR_FILENO, &data->backup_error) == -1)
		{
			g_status = 1;
			return (EXIT_FAILURE);
		}
	}
	if (mode == STD_RESTORE)
	{
		if (xdup2(data->backup_stdin, STDIN_FILENO) == -1 \
		|| xdup2(data->backup_stdout, STDOUT_FILENO) == -1 \
		|| xdup2(data->backup_error, STDERR_FILENO) == -1)
		{
			g_status = 1;
			exit(EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	no_pipe_and_builtcmd(t_nlst *node, t_data *data)
{
	if (backup_std_fd(data, STD_BACKUP) == EXIT_FAILURE)
	{
		close_redirect_fd(node->next);
		return ;
	}
	execute_command(node->next, data);
	close_redirect_fd(node->next);
	backup_std_fd(data, STD_RESTORE);
}

void	close_redirect_fd(t_nlst *node)
{
	t_redirect	*current;

	if (node->redirect->next != NULL)
	{
		current = node->redirect->next;
		while (current != node->redirect)
		{
			if (current->c_type == CHAR_LESSER \
			&& current->prev->c_type == HEAR_DOC)
			{
				current = current->next;
				continue ;
			}
			else if (current->c_type == HEAR_DOC \
			|| current->c_type == T_LESSER)
				xclose(current->next->heardoc_fd);
			else if (current->c_type == CHAR_LESSER)
				xclose(current->next->redirect_fd);
			else if (current->c_type == CHAR_GREATER \
			|| current->c_type == DGREATER)
				xclose(current->next->redirect_fd);
			current = current->next;
		}
	}
}

void	pipe_existence(t_nlst *node, t_data *data)
{
	t_nlst	*current;
	int		wstatus;

	xwaitpid(execution_process(node, data), &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_status = WEXITSTATUS(wstatus);
	current = node->next;
	while (current != node)
	{
		wait(0);
		close_redirect_fd(current);
		current = current->next;
	}
}

void	exection(t_nlst *node)
{
	t_data	data;
	t_nlst	*current;

	current = node->next;
	init_execution(&data, node);
	if (current->next == data.top \
	&& is_builtin_cmd(current->cmd->next->str) != OTHER)
		no_pipe_and_builtcmd(node, &data);
	else
		pipe_existence(node, &data);
	free_node(node);
}
