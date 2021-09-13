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
	else
		return (OTHER);
}

void	backup_std_fd(t_data *data, int mode)
{
	if (mode == STD_BACKUP)
	{
		data->backup_stdout = dup(STDIN_FILENO);
		data->backup_stdin = dup(STDOUT_FILENO);
		data->backup_error = dup(STDERR_FILENO);
	}
	if (mode == STD_RESTORE)
	{
		dup2(data->backup_stdout, STDIN_FILENO);
		dup2(data->backup_stdin, STDOUT_FILENO);
		dup2(data->backup_error, STDERR_FILENO);
	}
}

int	exection(t_nlst *node)
{
	t_data	data;
	t_nlst	*current;
	int	wstatus;

	current = node->next;
	init_execution(&data, node);
	if (current->next == data.top && is_builtin_cmd(current->cmd->next->str) != OTHER)
	{
		backup_std_fd(&data, STD_BACKUP);
		execute_command(current, &data);
		free_node(node);
		backup_std_fd(&data, STD_RESTORE);
	}
	else
	{
		backup_std_fd(&data, STD_BACKUP);
		waitpid(execution_process(node, &data), &wstatus, 0);
		//g_status =
		current = node->next;
		while (current != node)
		{
			wait(0);
			current = current->next;
		}
		free_node(node);
		backup_std_fd(&data, STD_RESTORE);
	}
	return (EXIT_SUCCESS);
}
