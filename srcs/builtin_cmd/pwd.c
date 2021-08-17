#include "../../libft/libft.h"
#include "builtin_cmd.h"
#include <errno.h>
#include <string.h>

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
	t_envlist	lst_init;
	t_envlist	lst;

	lst_init.prev = &lst;
	lst_init.next = &lst;
	lst_init.key = NULL;
	lst_init.value = NULL;
	lst.prev = &lst_init;
	lst.next = &lst_init;
	lst.key = "PWD";
	lst.value = getenv("PWD");
	if (my_pwd(&lst_init))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
