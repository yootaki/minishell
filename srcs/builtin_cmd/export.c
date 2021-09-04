#include "builtin_cmd.h"

/*	コンパイルコマンド
*	$ gcc -Wall -Wextra -Werror -o myexport export.c lst_func.c ../../libft/libft.a
*/

int	export(t_cmd_lst *cmd, t_envlist *envp_lst)
{
	t_cmd_lst	*now;
	t_envlist	*tmp;
	char		*env_key;
	char		*env_value;
	int			char_cnt;

	now = cmd->next->next;
	char_cnt = 0;
	while (now->str[char_cnt] != '=' && now->str[char_cnt])
		char_cnt++;
	env_key = (char *)malloc(sizeof(char) * (char_cnt + 1));
	if (!env_key)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	ft_strlcpy(env_key, now->str, char_cnt + 1);
	now->str += char_cnt + 1;
	env_value = (char *)malloc(sizeof(char) * (ft_strlen(now->str) + 1));
	ft_strlcpy(env_value, now->str, ft_strlen(now->str) + 1);
	tmp = envp_lst->next;
	while (tmp != envp_lst)
	{
		if (!ft_strncmp(tmp->key, env_key, ft_strlen(tmp->key) + 1))
			break ;
		tmp = tmp->next;
	}
	if (tmp != envp_lst)
		tmp->value = now->str;
	else
		ft_envlstadd_back(envp_lst, ft_envlstnew(env_key, env_value));
	free(env_key);
	free(env_value);
	return (EXIT_SUCCESS);
}

// int	my_export(char **argv, t_envlist *lst)
// {
// 	t_envlist	*tmp;
// 	char		*env_key;
// 	char		*env_value;
// 	int			char_cnt;

// 	argv++;
// 	char_cnt = 0;
// 	while (argv[0][char_cnt] != '=' && argv[0][char_cnt])
// 		char_cnt++;
// 	env_key = (char *)malloc(sizeof(char) * (char_cnt + 1));
// 	if (!env_key)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		return (EXIT_SUCCESS);
// 	}
// 	ft_strlcpy(env_key, argv[0], char_cnt + 1);
// 	argv[0] += char_cnt + 1;
// 	env_value = (char *)malloc(sizeof(char) * (ft_strlen(argv[0]) + 1));
// 	ft_strlcpy(env_value, argv[0], ft_strlen(argv[0]) + 1);
// 	tmp = lst->next;
// 	while (tmp != lst)
// 	{
// 		if (!ft_strncmp(tmp->key, env_key, ft_strlen(tmp->key) + 1))
// 			break ;
// 		tmp = tmp->next;
// 	}
// 	if (tmp != lst)
// 		tmp->value = argv[0];
// 	else
// 		ft_envlstadd_back(lst, ft_envlstnew(env_key, env_value));
// 	free(env_key);
// 	free(env_value);
// 	return (EXIT_SUCCESS);
// }

// int	main(int argc, char **argv)
// {
// 	t_envlist	lst_init;
// 	t_envlist	lst;

// 	if (argc < 2)
// 		return (EXIT_SUCCESS);
// 	lst_init.prev = &lst;
// 	lst_init.next = &lst;
// 	lst_init.key = NULL;
// 	lst_init.value = NULL;
// 	lst.prev = &lst_init;
// 	lst.next = &lst_init;
// 	lst.key = "PWD";
// 	lst.value = getenv("PWD");
// 	my_export(argv, &lst_init);
// 	return (EXIT_SUCCESS);
// }
