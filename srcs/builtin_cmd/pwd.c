#include "builtin_cmd.h"

int	my_pwd(t_envlist *lst)
{
	t_envlist	*tmp;
	
	tmp = lst->next;
	while (ft_strncmp(tmp->key, "PWD", 4) && tmp != lst)
		tmp = tmp->next;
	printf("%s\n", tmp->value);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	t_envlist	*init_lst;

	init_lst = ft_envlstnew(NULL, NULL);
	ft_envlstadd_back(init_lst, ft_envlstnew("PWD", getenv("PWD")));
	if (my_pwd(init_lst))
		return (EXIT_FAILURE);
	free_envlst(init_lst);
	return (EXIT_SUCCESS);
}
