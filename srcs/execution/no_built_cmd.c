#include "../../includes/execution.h"

void	check_std_fd_in_use(int  specified_fd, t_data *data)
{
	if (specified_fd == data->backup_stdout)
	{
		//printf("-------1------\n");
		data->backup_stdout = xdup(data->backup_stdout);
	}
	if (specified_fd == data->backup_stdin)
	{
		//printf("-------1------\n");
		data->backup_stdin = xdup(data->backup_stdin);
	}
	if (specified_fd == data->backup_error)
	{
		//printf("-------1------\n");
		data->backup_error = xdup(data->backup_error);
	}
		
}

void	change_fd(t_redirect *r_lst, int redirect_fd, int std_fd, t_data *data)
{
	if (r_lst->spec_flg == 1)
	{
		//printf("----change_fd-----\n");
		//printf("r_lst->spec_fd = %d\n", r_lst->spec_fd);
		check_std_fd_in_use(r_lst->spec_fd, data);
		xdup2(redirect_fd, r_lst->spec_fd);
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
			else if (current->c_type == HEAR_DOC || current->c_type == T_LESSER)
			{
				//printf("current->heardoc_fd = %d\n", current->heardoc_fd);
				//printf("current->next->heardoc_fd = %d\n", current->next->heardoc_fd);
				change_fd(current, current->next->heardoc_fd, STDIN_FILENO, data);
				/* if (current->spec_fd == 1)
				{
					check(current->spec_fd, data);
					xdup2(current->next->heardoc_fd, current->spec_fd);
				}
				else
					xdup2(current->next->heardoc_fd, STDIN_FILENO);
				xclose(current->next->heardoc_fd); */
			}
			else if (current->c_type == CHAR_LESSER)
			{
				change_fd(current, current->next->redirect_fd, STDIN_FILENO, data);
				/* if (current->spec_fd == 1)
				{
					check(current->spec_fd, data);
					xdup2(current->next->redirect_fd, current->spec_fd);
				}
				else
					xdup2(current->next->redirect_fd, STDIN_FILENO);
				xclose(current->next->redirect_fd); */
			}
			else if (current->c_type == CHAR_GREATER || current->c_type == DGREATER)
			{
				//printf("current->redirect_fd = %d\n",current->redirect_fd);
				//printf("current->next->redirect_fd = %d\n",current->next->redirect_fd);
				change_fd(current, current->next->redirect_fd, STDOUT_FILENO, data);
				/* if (current->spec_fd == 1)
				{
					check(current->spec_fd, data);
					xdup2(current->next->redirect_fd, current->spec_fd);
				}
				else
					xdup2(current->next->redirect_fd, STDOUT_FILENO);
				xclose(current->next->redirect_fd); */
			}
			current = current->next;
		}
	}
	//write(4, "hello", 5);
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
