#include "builtin_cmd.h"

int	pwd(t_envlist *envp_lst)
{
	t_envlist	*tmp;

	tmp = envp_lst->next;
	while (ft_strncmp(tmp->key, "PWD", 4) && tmp != envp_lst)
		tmp = tmp->next;
	printf("%s\n", tmp->value);
	return (EXIT_SUCCESS);
}
