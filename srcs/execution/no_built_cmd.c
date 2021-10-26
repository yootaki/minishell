/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_built_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:04:18 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/26 13:12:42 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	check_std_fd_in_use(int specified_fd, t_data *data)
{
	if (specified_fd == data->backup_stdout)
		return (xdup(data->backup_stdout, &data->backup_stdout));
	else if (specified_fd == data->backup_stdin)
		return (xdup(data->backup_stdin, &data->backup_stdin));
	else if (specified_fd == data->backup_error)
		return (xdup(data->backup_error, &data->backup_error));
	return (0);
}

int	change_fd(t_redirect *r_lst, int redirect_fd, int std_fd, t_data *data)
{
	if (r_lst->spec_flg == 1)
	{
		printf("----r_lst->spec_flg--\n");
		if (check_std_fd_in_use(r_lst->spec_fd, data) == -1 \
		|| xdup2(redirect_fd, r_lst->spec_fd) == -1)
		{
			g_status = 1;
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (xdup2(redirect_fd, std_fd) == -1)
		{
			g_status = 1;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	check_type_redirect(t_redirect **r_lst, t_data *data)
{
	if ((*r_lst)->c_type == CHAR_LESSER \
	&& (*r_lst)->prev->c_type == HEAR_DOC)
		return (0);
	else if ((*r_lst)->c_type == HEAR_DOC \
	|| (*r_lst)->c_type == T_LESSER)
		return (change_fd(*r_lst, (*r_lst)->next->heardoc_fd, \
		STDIN_FILENO, data));
	else if ((*r_lst)->c_type == CHAR_LESSER)
		return (change_fd(*r_lst, (*r_lst)->next->redirect_fd, \
		STDIN_FILENO, data));
	else if ((*r_lst)->c_type == CHAR_GREATER \
	|| (*r_lst)->c_type == DGREATER)
		return (change_fd(*r_lst, (*r_lst)->next->redirect_fd, \
		STDOUT_FILENO, data));
	return (0);
}

int	check_redirect(t_nlst *node, t_data *data)
{
	t_redirect	*current;

	if (node->redirect->next != NULL)
	{
		current = node->redirect->next;
		while (current != node->redirect)
		{
			if (check_type_redirect(&current, data) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			current = current->next;
		}
	}
	return (EXIT_SUCCESS);
}

void	no_built_cmd(t_nlst *node, t_data *data)
{
	g_status = 0;
	if (node->cmd->next->str == NULL)
		exit(g_status);
	data->cmd_array = create_cmd_array(node, data);
	if (execve(data->cmd_array[0], data->cmd_array, NULL) == -1)
	{
		ft_perror(data->cmd_array[0]);
		g_status = 1;
		exit(g_status);
	}
}
