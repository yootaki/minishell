# include "execution.h"

char	**search_path(t_envlist	*envp)
{
	t_envlist	*current;
	char	**path;

	current = envp->next;
	while (ft_strncmp(current->key, "PATH", 4) != 0 && current != envp)
		current = current->next;
	if (current == envp)
		return (NULL);
	path = ft_split(current->value, ':');
	if (path == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	return (path);
}

int	get_path(t_nlst *node, t_data *data)
{
	data->path_list = search_path(node->envp_lst);
	if (data->path_list == NULL)
		free_function(data, 1);
	return (EXIT_SUCCESS);
}
