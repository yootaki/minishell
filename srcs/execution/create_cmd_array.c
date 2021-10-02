#include "../../includes/execution.h"

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

char	**create_cmd_array(t_nlst *node, t_data *data)
{
	char	*tmp_cmd;

	get_path(node, data);
	data->cmd = get_cmd_str(node);
	if (data->cmd == NULL)
		free_function(data, 2);
	tmp_cmd = search_cmd(data->cmd[0], data);
	if (tmp_cmd == NULL)
		free_function(data, 3);
	data->cmd[0] = tmp_cmd;
	return (data->cmd);
}
