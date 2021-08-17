#include "../../libft/libft.h"
#include "builtin_cmd.h"
#include <errno.h>
#include <string.h>

# define CURRENTPATH_SIZE 512

/*	コンパイルコマンド
*	$ gcc -Wall -Wextra -Werror -o mycd cd.c ../../libft/libft.a
*/

int	my_cd(int argc, char **argv, t_envlist *lst)
{
	t_envlist	*tmp;
	char		current_path[CURRENTPATH_SIZE];
	char		*new_path;

	ft_memset(current_path, '\0', CURRENTPATH_SIZE);
	new_path = NULL;

	/* ディレクトリを変更 */
	if (argc < 2)
	{
		if (chdir(getenv("HOME")))
		{
			printf("%s\n", strerror(errno));
			return (EXIT_FAILURE);
		}
	}
	else
	{
		argv++;
		new_path = ft_strjoin("./", argv[0]);
		if (chdir(new_path))
		{
			printf("%s\n", strerror(errno));
			return (EXIT_FAILURE);
		}
	}
	getcwd(current_path, CURRENTPATH_SIZE);
	printf("変更後DIR:%s\n", current_path);

	/* $PWDを書きかえ */
	tmp = lst->next;
	while (ft_strncmp(tmp->key, "PWD", 4) && tmp != lst)
		tmp = tmp->next;
	tmp->value = current_path;
	printf("環境変数%s:%s\n", tmp->key, tmp->value);

	free(new_path);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
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
	if (my_cd(argc, argv, &lst_init))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
