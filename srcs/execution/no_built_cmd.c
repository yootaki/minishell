#include "execution.h"

void	check_std_fd_in_use(int  specified_fd, t_data *data)
{
	if (specified_fd == data->data->backup_stdout)
		data->backup_stdout = xdup(data->backup_stdout);
	if (specified_fd == data->data->backup_stdin)
		data->backup_stdin = xdup(data->backup_stdin);
	if (specified_fd == data->data->backup_error)
		data->backup_stderror = xdup(data->backup_stderror);
}

void	change_fd(int specified_fd, int redirect_fd, int std_fd, t_data *data)
{
	if (specified_fd == 1)
	{
		check(specified_fd, data);
		xdup2(redirect_fd, specified_fd);
	}
	else
		xdup2(redirect_fd, std_fd);
	xclose(redirect_fd);
}

void	check_redirect(t_nlst *node, t_data *data)
{
	t_redirect	*current;

	if (node->redirect->next != NULL)
	{
		current = node->redirect->next;
		while (current != node->redirect)
		{
			if (current->c_type == CHAR_LESSER && current->prev->c_type == HEAR_DOC)
			{
				current = current->next;
				continue ;
			}
			else if (current->c_type == HEAR_DOC)
			{
				if (current->specified_fd == 1)
				{
					check(current->specified_fd, data);
					xdup2(current->next->heardoc_fd, current->specified_fd);
				}
				else
					xdup2(current->next->heardoc_fd, STDIN_FILENO);
				xclose(current->next->heardoc_fd);
			}
			else if (current->c_type == CHAR_LESSER)
			{
				if (current->specified_fd == 1)
				{
					check(current->specified_fd, data);
					xdup2(current->next->redirect_fd, current->specified_fd);
				}
				else
					xdup2(current->next->redirect_fd, STDIN_FILENO);
				xclose(current->next->redirect_fd);
			}
			else if (current->c_type == CHAR_GREATER || current->c_type == DGREATER)
			{
				if (current->specified_fd == 1)
				{
					check(current->specified_fd, data);
					xdup2(current->next->redirect_fd, current->specified_fd);
				}
				else
					xdup2(current->next->redirect_fd, STDOUT_FILENO);
				xclose(current->next->redirect_fd);
			}
			current = current->next;
		}
	}
}

void	no_built_cmd(t_nlst *node, t_data *data)
{
	g_status = 0;
	check_redirect(node, data);
	data->cmd_array = create_cmd_array(node, data);
	if (execve(data->cmd_array[0], data->cmd_array, NULL) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(data->cmd_array[0]);
	}
}
