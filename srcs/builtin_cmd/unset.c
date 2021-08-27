#include "builtin_cmd.h"

/*
	<コンパイルコマンド>
	$ gcc -Wall -Wextra -Werror -o myunset unset.c lst_func.c ../../libft/libft.a

	<入力例>
	$ ./myunset PWD
	$ ./myunset TEST
*/

int	my_unset(char **argv, t_envlist *lst)
{
	t_envlist	*tmp;
	char		*env_key;
	int			char_cnt;

	argv++;
	char_cnt = 0;
	while (argv[0][char_cnt] != '=' && argv[0][char_cnt])
		char_cnt++;
	env_key = (char *)malloc(sizeof(char) * (++char_cnt));
	if (!env_key)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	ft_strlcpy(env_key, argv[0], char_cnt);
	tmp = lst->next;
	while (ft_strncmp(tmp->key, env_key, char_cnt) && tmp != lst)
		tmp = tmp->next;
	ft_envlstdelone(tmp);
	free(env_key);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_envlist	*init_lst;

	if (argc < 2)
		return (EXIT_SUCCESS);
	init_lst = ft_envlstnew(NULL, NULL);
	ft_envlstadd_back(init_lst, ft_envlstnew("TEST", "example"));
	ft_envlstadd_back(init_lst, ft_envlstnew("PWD", getenv("PWD")));

	printf("\n---unset前---\n");
	for (int j = 1; j < 4; j++)
	{
		printf("[%d]%s:%s\n", j, init_lst->key, init_lst->value);
		init_lst = init_lst->next;
	}
	my_unset(argv, init_lst);
	printf("\n---unset後---\n");
	for (int j = 1; j < 4; j++)
	{
		printf("[%d]%s:%s\n", j, init_lst->key, init_lst->value);
		init_lst = init_lst->next;
	}
	printf("\n");
	free_envlst(init_lst);
	return (EXIT_SUCCESS);
}
