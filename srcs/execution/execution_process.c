#include "execution.h"

void	ft_call_child(t_nlst *node, t_data *data, int *pipefd)
{
	t_redirect	*current;
	int	redirect_flg;

	close(pipefd[READ]);
	redirect_flg = -1;
	if (node->redirect->next != NULL)
	{
		current = node->redirect->next;
		while (current != node->redirect)
		{
			if (current->c_type == CHAR_GREATER)
			{
				printf("-------c_type-----\n");
				printf("current->redirect->str = %s\n", current->str);
				printf("current->redirect_fd = %d\n", current->redirect_fd);
				dup2(current->redirect_fd, STDOUT_FILENO);
				redirect_flg = 1;
			}
			current = current->next;
		}
	}
	if (node->next != data->top && redirect_flg == -1)
		dup2(pipefd[WRITE], STDOUT_FILENO);
	/* else
	{
		printf("node->next = %p | data->top = %p\n", node->next, data->top);
		printf("node->cmd = %s\n", node->cmd->next->str);
		dup2(data->backup_stdout, STDOUT_FILENO);
		close(data->backup_stdout);
		printf("STDOUT_FILENO = %d\n", STDOUT_FILENO);
	} */
	close(pipefd[WRITE]);
	data->cmd_array = create_cmd_array(node, data);
	printf("---------------\n");
	int i = 0;
	while (data->cmd_array[i] != NULL)
	{
		printf("data->cmd_array[%d] = %s\n", i, data->cmd_array[i]);
		i++;
	}
	printf("data->cmd_array = %s\n", data->cmd_array[1]);
	if (execve(data->cmd_array[0], data->cmd_array, NULL) == -1)
		perror("");
}

/*
 * とりあえず、大まかな流れだけ書いてますので、エラー対応などは一切してません。
 */

int	execution_process(t_nlst *node, t_data *data)
{
	t_nlst	*current;
	int	pipefd[FD_NUM];
	int	pid;
	//int flag;

	//printf("\n");
	//printf("-----execution_process_start-------\n");
	data->backup_stdout = dup(STDOUT_FILENO);
	current = node->next;
	int i = 0;
	while (current != node)
	{
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
		/* printf("pid = %d\n", pid);
		printf("str = %s\n", current->cmd->next->str); */
		if (pid == 0)
			ft_call_child(current, data, pipefd);
		//close(pipefd[WRITE]);
		//wait(0);
		printf("-------child_end[%d]---\n", i);
		//waitpid(pid, &flag, 0);
		if (dup2(pipefd[READ], STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		close(pipefd[READ]);
		free_data_lst(data);
		current = current->next;
		printf("----while_end[%d]-----\n", i);
		i++;
	}
	/* printf("\n");
	printf("-----execution_process_end-------\n"); */
	return (EXIT_SUCCESS);
}