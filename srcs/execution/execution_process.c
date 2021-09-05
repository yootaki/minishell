#include "execution.h"

void	ft_call_child(t_nlst *node, t_data *data, t_nlst *nil, int *pipefd)
{
	close(pipefd[READ]);
	/*if (node->next == nil)
	{
		printf("-----NULL-----\n");
		dup2(data->backup_stdout, STDOUT_FILENO);
		close(data->backup_stdout);
	}*/
	if (node->next != nil)
		dup2(pipefd[WRITE], STDOUT_FILENO);
	//close(pipefd[WRITE]);
	data->cmd_array = create_cmd_array(node, data);
	printf("------execve------\n");
	execve(data->cmd_array[0], data->cmd_array, NULL);
}

/*
 * とりあえず、大まかな流れだけ書いてますので、エラー対応などは一切してません。
 */

int	execution_process(t_nlst *node, t_data *data)
{
	t_nlst	*current;
	int	pipefd[FD_NUM];
	int	pid;

	printf("\n");
	printf("-----execution_process_start-------\n");
	data->backup_stdout = dup(STDOUT_FILENO);
	current = node->next;
	while (current != node)
	{
		printf("----while_start-----\n");
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
		printf("pid = %d\n", pid);
		printf("str = %s\n", current->cmd->next->str);
		if (pid == 0)
			ft_call_child(current, data, node, pipefd);
		//close(pipefd[WRITE]);
		if (dup2(pipefd[READ], STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		close(pipefd[READ]);
		free_data_lst(data);
		current = current->next;
		printf("----while_end-----\n");
	}
	printf("\n");
	printf("-----execution_process_end-------\n");
	return (EXIT_SUCCESS);
}