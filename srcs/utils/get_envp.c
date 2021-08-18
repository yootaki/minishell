#include "utils.h"

int	envp_lstmap(t_envlist *envp, char *key, char *value)
{
	t_envlist	*new_lst;

	new_lst = ft_envlstnew(key, value);
	if (new_lst == NULL)
	{
		free_envplist(envp);
		return (EXIT_FAILURE);
	}
	ft_envlstadd_back(envp, new_lst);
	return (EXIT_SUCCESS);
}

/*
* 環境変数を一行ずつ読み取り、keyとvalueに分割してenv_lstに追加
*/

int	create_envlst(t_envlist *lst, char **envp)
{
	t_envlist	*current;
	char	*str;
	char	*key;
	char	*value;

	current = lst;
	while (*envp != NULL)
	{
		str = *envp;
		printf("envp = %s\n", *envp);
		while (*str != '=')
			str++;
		*str = '\0';
		key = ft_strdup(*envp);
		str++;
		value = ft_strdup(str);
		if (!envp_lstmap(current, key, value))
			return (EXIT_FAILURE);
		(envp)++;
	}
	return (EXIT_SUCCESS);
}

int	get_envp(char **envp)
{
	t_envlist *env_lst;

	env_lst = init_envlist();
	if (env_lst == NULL)
		return (EXIT_FAILURE);
	create_envlst(env_lst, envp);
	return (EXIT_SUCCESS);
}
