#include "execution.h"
#include <sys/types.h>
#include <unistd.h>

static void	ft_call_child(t_nlst *node, t_data *data, int prev_read_fd, int *pipefd)
{
	t_redirect	*current;
	int	redirect_flg;

	//dup2(prev_read_fd, STDIN_FILENO);
	printf("prev_read_fd = %d\n", prev_read_fd);
	dup2(prev_read_fd, STDIN_FILENO);
	close(pipefd[READ]);
	redirect_flg = -1;
	if (node->redirect->next != NULL)
	{
		current = node->redirect->next;
		while (current != node->redirect)
		{
			if (current->c_type == CHAR_GREATER || current->c_type == DGREATER)
			{
				printf("-------c_type-----\n");
				printf("current->redirect->str = %s\n", current->str);
				printf("current->redirect_fd = %d\n", current->next->redirect_fd);
				dup2(current->next->redirect_fd, STDOUT_FILENO);
				//close(current->next->redirect_fd);
				redirect_flg = 1;
			}
			current = current->next;
		}
	}
	if (node->next != data->top && redirect_flg == -1)
		dup2(pipefd[WRITE], STDOUT_FILENO);
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

static int	ft_call_parent(t_nlst *node, t_data *data, int prev_read_fd, int *pipefd)
{
	close(pipefd[WRITE]);
	printf("pipefd[READ] = %d\n", pipefd[READ]);
	if (prev_read_fd != STDIN_FILENO)
		close(prev_read_fd);
	if (node->next == data->top)
	{
		printf("------last----\n");
		close(pipefd[READ]);
		printf("pipefd[READ] = %d\n", pipefd[READ]);
	}
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
	int	backup_stdin;
	int	prev_read_fd;
	int			wstatus;

	data->backup_stdout = dup(STDOUT_FILENO);
	prev_read_fd = STDIN_FILENO;
	backup_stdin = dup(STDIN_FILENO);
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
		/* printf("pid = %d\n", pid);
		printf("str = %s\n", current->cmd->next->str); */
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
	printf("current = %p\n", current);
	dup2(data->backup_stdout, STDOUT_FILENO);
	close(data->backup_stdout);
	dup2(backup_stdin, STDIN_FILENO);
	close(backup_stdin);
	printf("\n");
	printf("-----execution_process_end-------\n");
	waitpid(pid, &wstatus, 0);
	//*(data->status) = WEXITSTATUS(wstatus);
	current = node->next;
	while (current != node)
	{
		//waitpid(0, NULL, 0);
		wait(0);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}