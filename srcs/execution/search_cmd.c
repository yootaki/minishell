#include "execution.h"

t_mode_type	ft_stat(char *pathname)
{
	struct stat buf;

	if (stat(pathname, &buf) == -1)
		return (ERROR);
	if ((buf.st_mode & S_IFMT) == S_IFREG)
		return (IS_FILE);
	else if ((buf.st_mode & S_IFMT) == S_IFDIR)
		return (IS_DIR);
	return (ELSE_MODE);
}

char	*strjoin_2times(char *path, const char *str, char *cmd)
{
	char	*tmp_path_cmd;
	char	*path_cmd;

	tmp_path_cmd = ft_strjoin(path, str);
	if (tmp_path_cmd == NULL)
		return (NULL);
	path_cmd = ft_strjoin(tmp_path_cmd, cmd);
	if (path_cmd == NULL)
	{
		free(tmp_path_cmd);
		return (NULL);
	}
	free(tmp_path_cmd);
	return (path_cmd);
}

char	*cmd_path_direct(char *cmd)
{
	t_mode_type mode_type;

	mode_type = ft_stat(cmd);
	if (mode_type == ERROR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmd);
		ft_exit(127);
	}
	else if (mode_type == IS_FILE)
		return (cmd);
	else if (mode_type == IS_DIR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		ft_exit(126);
	}
	return (cmd);
}

char	*cmd_path(char *cmd, t_data *data)
{
	int	i;
	char	*path_cmd;

	i = 0;
	while (data->path_list[i] != NULL)
	{
		path_cmd = strjoin_2times(data->path_list[i], "/", cmd);
		if (path_cmd == NULL)
			return (NULL);
		if (ft_stat(path_cmd) == IS_FILE) // 実行ファイルがあって、且つ実行権限がある場合
			break ;
		free(path_cmd);
		i++;
	}
	if (data->path_list[i] == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free_node(data->top);
		ft_exit(127);
	}
	free (cmd);
	return (path_cmd);
}

char	*search_cmd(char *cmd, t_data *data)
{
	char	*path_cmd;
	if (ft_strchr(cmd, '/') || (ft_strchr(cmd, '.') && ft_strchr(cmd, '/')))
		path_cmd = cmd_path_direct(cmd);
	else
		path_cmd = cmd_path(cmd, data);
	return (path_cmd);
}