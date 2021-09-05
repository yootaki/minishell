#include "execution.h"

void	free_path_lst(t_data *data)
{
	int	i;

	i = 0;
	while (data->path_list[i] != NULL)
	{
		free(data->path_list[i]);
		//data->path_list[i] = NULL;
		i++;
	}
	free(data->path_list);
	data->path_list = NULL;
}

void	free_data_lst(t_data *data)
{
	//free_path_lst(data);
	free(data->cmd_array);
}

void	free_all(char **cmd_array, t_nlst *node, t_data *data)
{
	free(cmd_array);
	free_node(node);
	free_data_lst(data);
	exit(1);
}