#include "execution.h"

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
		//printf("current->str = %s\n", current->str);
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

char	*search_cmd(char *cmd, t_data *data)
{
	struct stat      stat_buf;
	char	*path_cmd;
	int	i;

	i = 0;
	while (data->path_list[i] != NULL)
	{
		path_cmd = strjoin_2times(data->path_list[i], "/", cmd);
		if (path_cmd == NULL)
			return (NULL);
		if (stat(path_cmd, &stat_buf) == 0) // 実行ファイルがあって、且つ実行権限がある場合
			if ((stat_buf.st_mode & S_IXUSR))
				break ;
		free(path_cmd);
		i++;
	}
	if (data->path_list[i] == NULL)
		return (cmd);
	free (cmd);
	return (path_cmd);
}

char	**create_cmd_array(t_nlst *node, t_data *data)
{
	char	**cmd_array;
	char	*tmp_cmd;

	//printf("------create_cmd_array_start------\n");
	get_path(node, data);
	cmd_array = get_cmd_str(node);
	if (cmd_array == NULL)
		return (NULL); // mallocエラー
	tmp_cmd = search_cmd(cmd_array[0], data);
	/*if (tmp_cmd == cmd_array[0]) // cmd_pathがない場合
		free_no_cmd(cmd_array, node, data);*/ //とりあえずNULL (exit()で終了予定)
	if (tmp_cmd == NULL) // malloc失敗した場合
		free_all(cmd_array, node, data); //とりあえずNULL (exit()で終了予定)
	cmd_array[0] = tmp_cmd; // cmd_pathをcmd_array[0]に代入
	/* printf("cmd_array[0] = %s\n", cmd_array[0]);
	printf("cmd_array[1] = %s\n", cmd_array[1]);
	printf("------create_cmd_array_end------\n");
	printf("\n");  */
	return (cmd_array);
}