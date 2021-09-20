#include "execution.h"
#include "../builtin_cmd/builtin_cmd.h"

void	init_execution(t_data *data, t_nlst *node)
{
	data->cmd_array = NULL;
	data->path_list = NULL;
	data->cmd = NULL;
	data->top = node;
	data->backup_stdout = -1;
	data->backup_stdin = -1;
	data->backup_error = -1;
}

enum e_STD_FD
{
	STD_BACKUP,
	STD_RESTORE,
};

enum	e_built
{
	ECHO,
	CD,
	ENV,
	EXPORT,
	PWD,
	UNSET,
	EXIT,
	OTHER
};

int	g_status;

int	is_builtin_cmd(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (ECHO);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (CD);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (ENV);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (EXPORT);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (PWD);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (UNSET);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (EXIT);
	else
		return (OTHER);
}

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
