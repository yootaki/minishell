#include "builtin_cmd.h"

/*
現在設定されている環境変数の一覧が表示
*/

int	my_env(t_envlist *lst)
{
	t_envlist	*tmp;

	tmp = lst->next;
	while (tmp != lst)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	main(void)
{
	t_envlist	*init_lst;

	init_lst = ft_envlstnew(NULL, NULL);
	ft_envlstadd_back(init_lst, ft_envlstnew("TEST", "example"));
	ft_envlstadd_back(init_lst, ft_envlstnew("PWD", getenv("PWD")));
	ft_envlstadd_back(init_lst, ft_envlstnew("NULL", ""));

	my_env(init_lst);

	free_envlst(init_lst);
	return (EXIT_SUCCESS);
}
