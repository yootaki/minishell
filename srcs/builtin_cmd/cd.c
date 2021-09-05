#include "builtin_cmd.h"

/* !!!mallocして返してる!!! */
int	cd(t_cmd_lst *cmd, t_envlist *envp_lst)
{
	t_cmd_lst	*now;
	t_envlist	*tmp;
	char		*dir_path;

	now = cmd->next->next;
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
	change_current_path(envp_lst->next);
	tmp = envp_lst->next;
	while (ft_strncmp(tmp->key, "PWD", 4) && tmp != envp_lst)
		tmp = tmp->next;
	return (EXIT_SUCCESS);
}
