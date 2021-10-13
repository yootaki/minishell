/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:04:06 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/13 20:09:58 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../builtin_cmd/builtin_cmd.h"

void	backup_std_fd(t_data *data, int mode)
{
	if (mode == STD_BACKUP)
	{
		data->backup_stdout = xdup(STDIN_FILENO);
		data->backup_stdin = xdup(STDOUT_FILENO);
		data->backup_error = xdup(STDERR_FILENO);
	}
	if (mode == STD_RESTORE)
	{
		xdup2(data->backup_stdout, STDIN_FILENO);
		xdup2(data->backup_stdin, STDOUT_FILENO);
		xdup2(data->backup_error, STDERR_FILENO);
	}
}

void	no_pipe_and_builtcmd(t_nlst *node, t_data *data)
{
	backup_std_fd(data, STD_BACKUP);
	execute_command(node->next, data);
	free_node(node);
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

	backup_std_fd(data, STD_BACKUP);
	xwaitpid(execution_process(node, data), &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_status = WEXITSTATUS(wstatus);
	current = node->next;
	while (current != node)
	{
		wait(NULL);
		close_redirect_fd(current);
		current = current->next;
	}
	free_node(node);
	backup_std_fd(data, STD_RESTORE);
}

int	exection(t_nlst *node)
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
	return (EXIT_SUCCESS);
}
