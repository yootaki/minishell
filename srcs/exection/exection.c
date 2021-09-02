#include "../../includes/input.h"
#include "../../includes/parse.h"
#include "../../includes/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

int	echo(t_cmd_lst *cmd);
int	cd(t_cmd_lst *cmd, t_envlist *envp_lst);
int	env(t_envlist *envp_lst);
int	export(t_cmd_lst *cmd, t_envlist *envp_lst);

typedef struct s_data
{
	char	**path_list;
}		t_data;

char	**search_path(t_envlist	*envp)
{
	t_envlist	*current;
	char	**path;
	int	i;

	current = envp->next;
	i = 0;
	while (ft_strncmp(current->key, "PATH", 4) != 0 && current != envp)
		current = current->next;
	if (current == envp)
		return (NULL);
	path = ft_split(current->value, ':');
	if (path == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	return (path);
}

/*int	file_access(t_nlst **node)
{
	t_cmd_lst	*cmd;

	if (node == NULL)
		return (EXIT_FAILURE);
	if ((*node)->next->cmd->next != NULL)
		cmd = node->next->cmd->next;
	if (cmd->category == ISFILE)
}*/

int	get_path(t_nlst *node, t_data *data)
{
	data->path_list = search_path(node->next->envp_lst);
	if (data->path_list == NULL)
		return (EXIT_FAILURE);
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

enum	e_fd
{
	READ,
	WRITE,
	FD_NUM
};

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

	cmd_array = get_cmd_str(node);
	if (cmd_array == NULL)
		return (NULL);
	tmp_cmd = search_cmd(cmd_array[0], data);
	if (tmp_cmd == cmd_array[0]) // cmd_pathがない場合
		return (NULL); //とりあえずNULL
	if (tmp_cmd == NULL) // malloc失敗した場合
		return (NULL); //とりあえずNULL
	cmd_array[0] = tmp_cmd;
	return (cmd_array);

}

int	ft_call_child(t_nlst *node, t_data *data, int pipefd)
{
	char	**cmd_array;

	close(pipefd[READ]);
	if () // redirectがない場合
		dup2(pipefd[WRITE], WRITE);
	else
		dup2(); //redirectのfdを書き込み専用fdに複製
	close(pipefd[WRITE]);
	cmd_array = create_cmd_array(node, data);
	if (execve(cmd_array[0], cmd_array, NULL) == -1)
		perror("exeve");
	
}

/*
 * とりあえず、大まかな流れだけ書いてますので、エラー対応などは一切してません。
 */

void	exection_process(t_nlst *node, t_data *data)
{
	t_nlst	*current;
	int	pipefd[FD_NUM];
	int	pid;

	current = node->next;
	while (current != node)
	{
		if (pipe(pipefd) == -1)
			return ;
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			fd_call_child();
	}
}

int	exection(t_nlst *node)
{
	t_data	data;
	char	*cmd;

	cmd = node->next->cmd->next->str;
	//コマンドがビルトインかどうか判定
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		echo(node->next->cmd);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		cd(node->next->cmd, node->next->envp_lst);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		env(node->next->envp_lst);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		export(node->next->cmd, node->next->envp_lst);
	else
		exection_process(node, data);
	
	return (EXIT_SUCCESS);
}
