#include "execution.h"

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

void	pipe_existence(t_nlst *node, t_data *data)
{
	t_nlst	*current;
	int	wstatus;

	backup_std_fd(data, STD_BACKUP);
	xwaitpid(execution_process(node, data), &wstatus, 0);
	g_status = WEXITSTATUS(wstatus);
	current = node->next;
	while (current != node)
	{
		wait(0);
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
	if (current->next == data.top && is_builtin_cmd(current->cmd->next->str) != OTHER)
		no_pipe_and_builtcmd(node, &data);
	else
		pipe_existence(node, &data);
	return (EXIT_SUCCESS);
}
