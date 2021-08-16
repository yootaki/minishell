#include "../../libft/libft.h"
#include "builtin_cmd.h"
#include <errno.h>
#include <string.h>

/*	コンパイルコマンド
*	$ gcc -Wall -Wextra -Werror -o myexport export.c lst_func.c ../../libft/libft.a
*/

int	my_export(char **argv, t_envlist *lst)
{
	t_envlist	*tmp;
	char		*env_key;
	char		*env_value;
	int			char_cnt;

	argv++;
	char_cnt = 0;
	while (argv[0][char_cnt] != '=' && argv[0][char_cnt])
		char_cnt++;
	env_key = (char *)malloc(sizeof(char) * (char_cnt + 1));
	if (!env_key)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	ft_strlcpy(env_key, argv[0], char_cnt + 1);
	argv[0] += char_cnt + 1;
	env_value = (char *)malloc(sizeof(char) * (ft_strlen(argv[0]) + 1));
	ft_strlcpy(env_value, argv[0], ft_strlen(argv[0]) + 1);

	/* リストに指定された環境変数があるか確認 */
	tmp = lst->next;
	while (tmp != lst)
	{
		if (!ft_strncmp(tmp->key, env_key, ft_strlen(tmp->key) + 1))
			break ;
		tmp = tmp->next;
	}
	if (tmp != lst)// 環境変数が存在する場合
	{
		tmp->value = argv[0];
		printf("env_key   : %s\n", env_key);
		printf("env_value : %s\n", env_value);
		printf("$PWD      : %s\n", tmp->value);
	}
	else
	{
		ft_envlstadd_back(lst, ft_envlstnew(env_key, env_value));
		printf("env_key : %s\n", env_key);
		printf("env_value : %s\n", env_value);
		printf("$%s : %s\n", lst->prev->key, lst->prev->value);
	}

	free(env_key);
	free(env_value);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_envlist	lst_init;
	t_envlist	lst;

	if (argc < 2)
		return (EXIT_SUCCESS);
	lst_init.prev = &lst;
	lst_init.next = &lst;
	lst_init.key = NULL;
	lst_init.value = NULL;
	lst.prev = &lst_init;
	lst.next = &lst_init;
	lst.key = "PWD";
	lst.value = getenv("PWD");
	my_export(argv, &lst_init);
	return (EXIT_SUCCESS);
}
