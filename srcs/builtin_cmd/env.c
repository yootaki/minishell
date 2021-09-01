#include "builtin_cmd.h"

/*
現在設定されている環境変数の一覧が表示
*/

int	env(t_envlist *envp_lst)
{
	t_envlist	*tmp;

	tmp = envp_lst->next;
	while (tmp != envp_lst)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
