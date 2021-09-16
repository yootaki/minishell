#include "execution.h"

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
