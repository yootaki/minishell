#include "execution.h"
#include <sys/types.h>
#include <unistd.h>

void	check_redirect(t_nlst *node)
{
	t_redirect	*current;

	if (node->redirect->next != NULL)
	{
		current = node->redirect->next;
		while (current != node->redirect)
		{
			if (current->c_type == HEAR_DOC)
			{
				dup2(current->next->heardoc_fd[READ], STDIN_FILENO);
				close(current->next->heardoc_fd[READ]);
			}
			if (current->c_type == CHAR_LESSER)
			{
				dup2(current->next->redirect_fd, STDIN_FILENO);
				close(current->next->redirect_fd);
			}
			if (current->c_type == CHAR_GREATER || current->c_type == DGREATER)
			{
				dup2(current->next->redirect_fd, STDOUT_FILENO);
				close(current->next->redirect_fd);
			}
			current = current->next;
		}
	}
}

void	no_built_cmd(t_nlst *node, t_data *data)
{
	check_redirect(node);
	data->cmd_array = create_cmd_array(node, data);
	if (execve(data->cmd_array[0], data->cmd_array, NULL) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(data->cmd_array[0]);
	}
}

void	execute_command(t_nlst *node, t_data *data)
{
	char	*cmd;

	cmd = node->cmd->next->str;
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		my_echo(node->cmd, node->redirect);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		my_cd(node->cmd, node->envp_lst);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		my_env(node->envp_lst);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		my_export(node->cmd, node->envp_lst);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		my_pwd(node->envp_lst);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		my_unset(node->cmd, node->envp_lst);
	else
		no_built_cmd(node, data);
}

void	ft_call_child(t_nlst *node, t_data *data, int prev_read_fd, int *pipefd)
{
	dup2(prev_read_fd, STDIN_FILENO);
	close(pipefd[READ]);
	if (node->next != data->top)
		dup2(pipefd[WRITE], STDOUT_FILENO);
	close(pipefd[WRITE]);
	execute_command(node, data);
	exit(0);
}

int	ft_call_parent(t_nlst *node, t_data *data, int prev_read_fd, int *pipefd)
{
	close(pipefd[WRITE]);
	if (prev_read_fd != STDIN_FILENO)
		close(prev_read_fd);
	if (node->next == data->top)
		close(pipefd[READ]);
	return (pipefd[READ]);
}

/*
 * とりあえず、大まかな流れだけ書いてますので、エラー対応などは一切してません。
 */

int	execution_process(t_nlst *node, t_data *data)
{
	t_nlst	*current;
	int	pipefd[FD_NUM];
	int	pid;
	int	prev_read_fd;

	prev_read_fd = STDIN_FILENO;
	current = node->next;
	int i = 0;
	while (current != node)
	{
		printf("top%p = node %p\n", data->top, node);
		printf("----while_start[%d]-----\n", i);
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			return (EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (EXIT_FAILURE);
		}
		if (pid == 0)
		{
			printf("prev_read_fd = %d\n", prev_read_fd);
			printf("[%d]回目 [CHILD_PID_1 = %d]\n", i, getpid());
			ft_call_child(current, data, prev_read_fd, pipefd);
			printf("-------child_end[%d]---\n", i);
		}	
		else
		{
			printf("-------parent_start[%d]---\n", i);
			printf("prev_read_fd = %d\n", prev_read_fd);
			printf("[%d]回目 [pid = %d][PARENT_PID_1 = %d]\n", i, pid, getpid());
			prev_read_fd = ft_call_parent(current, data, prev_read_fd, pipefd);
			printf("prev_read_fd = %d\n", prev_read_fd);
			printf("-------parent_end[%d]---\n", i);
		}	
		free_data_lst(data);
		current = current->next;
		printf("----while_end[%d]-----\n\n", i);
		i++;
	}
	return (pid);
}