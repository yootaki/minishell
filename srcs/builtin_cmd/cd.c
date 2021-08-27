#include "builtin_cmd.h"

# define CURRENTPATH_SIZE 512

/* !!!mallocして返してる!!! */
int	my_cd(int argc, char **argv, t_envlist *lst)
{
	t_envlist	*tmp;
	char		current_path[CURRENTPATH_SIZE];
	char		*dir_path;

	ft_memset(current_path, '\0', CURRENTPATH_SIZE);
	if (argc < 2)
		dir_path = getenv("HOME");
	else
	{
		argv++;
		dir_path = argv[0];
	}
	if (chdir(dir_path))
	{
		perror(dir_path);
		return (EXIT_FAILURE);
	}

	/* $PWDを書きかえ */
	if (!getcwd(current_path, CURRENTPATH_SIZE))
		return (EXIT_FAILURE);
	tmp = lst->next;
	while (ft_strncmp(tmp->key, "PWD", 4) && tmp != lst)
		tmp = tmp->next;
	tmp->value = ft_strdup(current_path);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_envlist	*init_lst;
	char		buf[512];

	init_lst = ft_envlstnew(NULL, NULL);
	ft_envlstadd_back(init_lst, ft_envlstnew("PWD", getenv("PWD")));
	if (my_cd(argc, argv, init_lst))
		return (EXIT_FAILURE);
	printf("変更後DIR:%s\n", getcwd(buf, 512));
	printf("環境変数$PWD:%s\n", init_lst->next->value);
	free(init_lst->next->value);
	free_envlst(init_lst);
	return (EXIT_SUCCESS);
}
