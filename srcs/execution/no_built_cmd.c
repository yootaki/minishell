#include "execution.h"

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
				xdup2(current->next->heardoc_fd, STDIN_FILENO);
				xclose(current->next->heardoc_fd);
			}
			if (current->c_type == CHAR_LESSER)
			{
				xdup2(current->next->redirect_fd, STDIN_FILENO);
				xclose(current->next->redirect_fd);
			}
			if (current->c_type == CHAR_GREATER || current->c_type == DGREATER)
			{
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
	check_redirect(node);
	data->cmd_array = create_cmd_array(node, data);
	if (execve(data->cmd_array[0], data->cmd_array, NULL) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(data->cmd_array[0]);
	}
}
