#include "../builtin_cmd/builtin_cmd.h"
#include "expansion.h"

enum	e_fd
{
	READ,
	WRITE,
	FD_NUM
};

char	*expansion_hear_doc(char *line, t_envlist *env)
{
	char	*var_name;
	char	*var_value;
	char	*newline;
	char	*tmp;
	int		line_cnt;

	line_cnt = 0;
	while (line[line_cnt] != '$' && line[line_cnt] != '\0')
		line_cnt++;
	if (line[line_cnt] == '\0')
		return (line);
	line[line_cnt] = '\0';
	var_name = get_var_name(&line[line_cnt + 1]);
	var_value = ft_strdup(get_var_value(var_name, env));
	tmp = ft_strjoin(line, var_value);
	newline = ft_strjoin(tmp, &line[line_cnt + ft_strlen(var_name) + 1]);
	free(var_name);
	free(var_value);
	free(tmp);
	return (newline);
}

void	ft_putstr_endl(char *line, int *pipe_fd)
{
	ft_putstr_fd("> ", 1);
	ft_putendl_fd(line, pipe_fd[WRITE]);
}

/*
見つかったら1、見つからなければ0を返す。
この関数だとカレントディレクトリには対応できているけど、
(../srcs/file1)みたいな相対パスもしくは絶対パスには対応できていない。
パスに対応するにはft_strrchr使えばいけそうな気がする。
*/
int	find_and_create_file(char *file_name)
{
	char			pathname[512];
	DIR				*dp;
	struct dirent	*dirp;
	struct stat		buf;

	getcwd(pathname, 512);
	dp = opendir(pathname);
	while (1)
	{
		dirp = readdir(dp);
		if (dirp == NULL)
			break ;
		stat(dirp->d_name, &buf);
		if (S_ISREG(buf.st_mode) && dirp->d_name == file_name)
			return (1);
	}
	/* ファイルが見つからなかった場合作成する */

	closedir(dp);
	return (0);
}

int	hear_doc(t_redirect *redirect, t_envlist *env)
{
	t_redirect	*now;
	//hear_doc--------------------
	int			pipe_fd[FD_NUM];
	char		*expanded_line;
	char		*line;
	char		*separator;
	int			status;
	//----------------------------

	now = redirect->next;
	//heardocもリダイレクトもない場合は終了
	if (now->str == NULL)
		return (EXIT_SUCCESS);

	while (now != redirect)
	{
		//heardocの処理
		if (!ft_strncmp(now->str, "<<", ft_strlen(now->str)))
		{
			now = now->next;
			if (now->str == NULL)//このエラー文はこの出し方が正解？
				printf("bash: syntax error near unexpected token `newline'\n");
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			separator = now->str;
			ft_putstr_fd("> ", 1);
			while (1)
			{
				status = get_next_line(0, &line);
				if (!ft_strncmp(line, separator, ft_strlen(separator) + 1))
					break ;

				//読み込んだlineの変数を展開する（mallocしてる）
				expanded_line = expansion_hear_doc(line, env);
				printf("%s\n", expanded_line);

				if (status == 1)
					ft_putstr_endl(expanded_line, pipe_fd);
				if (status == 0)
					ft_putstr_fd(expanded_line, pipe_fd[WRITE]);
				free(line);
				// free(expanded_line);
				if (status == -1)
				{
					perror("malloc");
					exit(EXIT_FAILURE);
				}
			}
			free(line);
			// free(expanded_line);
		}

		//redirectの処理
		if (!ft_strncmp(now->str, ">", ft_strlen(now->str)) || !ft_strncmp(now->str, ">>", ft_strlen(now->str)))
		{
			now = now->next;
			if (now->str == NULL)
				printf("bash: syntax error near unexpected token `newline'\n");
			//ファイルを探す
			if (find_and_create_file(now->str))//みつからなければファイルを作成する
				printf("no such file or directory\n");
		}

		now = now->next;
	}

	return (EXIT_SUCCESS);
}
