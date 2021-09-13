#include "execution.h"

static void	free_path_list(char **path_list)
{
	int	i;

	i = 0;
	if (path_list == NULL)
		return ;
	while (path_list[i] != NULL)
	{
		free(path_list[i]);
		i++;
	}
	free(path_list);
	path_list = NULL;
}

void	free_function(t_data *data, int pattern)
{
	if (pattern == 1)
	{
		free_node(data->top);
	}
	if (pattern == 2)
	{
		free_path_list(data->path_list);
		free_node(data->top);
	}
	if (pattern == 3)
	{
		free(data->cmd);
		data->cmd = NULL;
		free_path_list(data->path_list);
		free_node(data->top);
	}
	exit(EXIT_FAILURE);
}

int	cmd_lst_len(t_cmd_lst *cmd)
{
	int	i;
	t_cmd_lst	*current;

	i = 0;
	current = cmd->next;
	while (current != cmd)
	{
		current = current->next;
		i++;
	}
	return (i);
}

char	**get_cmd_str(t_nlst *node)
{
	t_cmd_lst	*current;
	char	**cmd_array;
	int	i;

	cmd_array = (char **)malloc(sizeof(char *) * (cmd_lst_len(node->cmd) + 1));
	if (cmd_array == NULL)
		return (NULL);
	current = node->cmd->next;
	i = 0;
	while (current != node->cmd)
	{
		cmd_array[i] = current->str;
		current = current->next;
		i++;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
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

typedef enum e_mode_type
{
	ERROR,
	IS_FILE,
	IS_DIR,
	ELSE_MODE
}	t_mode_type;

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

char	*cmd_path_direct(char *cmd)
{
	t_mode_type mode_type;

	mode_type = ft_stat(cmd);
	if (mode_type == ERROR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmd);
		exit(127);
	}
	else if (mode_type == IS_FILE)
		return (cmd);
	else if (mode_type == IS_DIR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		exit(126);
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
		exit(127);
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

char	**create_cmd_array(t_nlst *node, t_data *data)
{
	char	*tmp_cmd;

	get_path(node, data);
	data->cmd = get_cmd_str(node);
	if (data->cmd == NULL)
		free_function(data, 2);
	tmp_cmd = search_cmd(data->cmd[0], data);
	if (tmp_cmd == NULL)
		free_function(data, 3);
	data->cmd[0] = tmp_cmd;
	return (data->cmd);
}