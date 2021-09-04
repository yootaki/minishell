#include "builtin_cmd.h"

/* !!!mallocして返してる!!! */
int	cd(t_cmd_lst *cmd, t_envlist *envp_lst)
{
	t_cmd_lst	*now;
	t_envlist	*tmp;
	char		current_path[CURRENTPATH_SIZE];
	char		*dir_path;

	now = cmd->next->next;
	ft_memset(current_path, '\0', CURRENTPATH_SIZE);
	if (now->str == NULL)
	{
		tmp = envp_lst->next;
		while (ft_strncmp(tmp->key, "HOME", 4) && tmp != envp_lst)
			tmp = tmp->next;
		dir_path = tmp->value;
	}
	else
		dir_path = now->str;
	if (chdir(dir_path))
	{
		perror(dir_path);
		return (EXIT_FAILURE);
	}
	/* $PWDを書きかえ */
	if (!getcwd(current_path, CURRENTPATH_SIZE))
		return (EXIT_FAILURE);
	tmp = envp_lst->next;
	while (ft_strncmp(tmp->key, "PWD", 4) && tmp != envp_lst)
		tmp = tmp->next;
	tmp->value = ft_strdup(current_path);
	return (EXIT_SUCCESS);
}
