#include "../builtin_cmd/builtin_cmd.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum e_tokentype
{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_WHITESPACE = ' ',
	CHAR_TAB = '\t',
	CHAR_ESCAPE = '\\',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	HEAR_DOC,
	DLESSER = 64,
}		t_token_type;

typedef struct s_cmd_lst
{
	struct	s_cmd_lst	*next;
	struct	s_cmd_lst	*prev;
	t_token_type	c_type;
	char	*str;
}		t_cmd_lst;

typedef struct	s_redirect
{
	struct s_redirect	*next;
	struct s_redirect	*prev;
	t_token_type	c_type;
	char	*str;
	char	*limmiter;
}		t_redirect;

typedef struct s_nlst
{
	t_cmd_lst	*cmd;
	t_redirect	*redirect;
	struct s_nlst	*next;
	struct s_nlst	*prev;
}		t_nlst;


//==============================================================================

//echo "Hello w$TEST yootaki" "Hello w"'orld' "Hello w" 'orld'
/*

1: Hello w\0 <- $を\0に置き換える
2: TEST <- orldに置き換える
3:  yootaki

これを環境変数が来るたびに行う
*/

typedef struct s_expanser
{
	char	*str;
	int	str_cnt;
}t_expanser;

char	*get_var_name(char *str)
{
	char	*var_name;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' ')//ここの条件もう少し考えるべき
		i++;
	var_name = (char*)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(var_name, str, i + 1);
	return (var_name);
}

char	*get_env_var_value(char *str, t_envlist *env)
{
	t_envlist	*now;
	char		*var_value;

	now = env->next;
	while (now != env)
	{
		if (!ft_strncmp(now->key, str, ft_strlen(str)))
			return (now->value);
		now = now->next;
	}
	return ("");
}

void	expansion_var(t_expanser *expanser, t_envlist *env)
{
	char	*var_name;
	char	*var_value;
	char	*new_str;
	char	*tmp;
	/* ->"Hello w$TEST yootaki"
	var[1] = "TEST(orld)"
	var[2] = " yootaki"
	var[3] = tmpとして使う
	*/

	//'$'->'\0' & 変数名を取得
	expanser->str[expanser->str_cnt] = '\0';
	var_name = get_var_name(&expanser->str[expanser->str_cnt + 1]);
	//変数の値を取得
	var_value = ft_strdup(get_env_var_value(var_name, env));

	//tmp = "Hello w\0"とvar_valueをjoin
	tmp = ft_strjoin(expanser->str, var_value);
	//tmpとexpanser->str[expanser->str_cnt]をjoin
	//"Hello world yootaki" が完成
	new_str = ft_strjoin(tmp, &expanser->str[expanser->str_cnt + ft_strlen(var_name) + 1]);
	//変数名の後までインデックスを進める( yootaki)
	expanser->str_cnt += ft_strlen(var_value);
	free(var_name);
	free(var_value);
	free(tmp);
	free(expanser->str);
	expanser->str = new_str;
	// printf("%s,%zu\n", &expanser->str[expanser->str_cnt], ft_strlen(&expanser->str[expanser->str_cnt]));
	// printf("%s,%zu\n", expanser->str, ft_strlen(expanser->str));
}

int	expanser(t_cmd_lst *cmd, t_envlist *env)
{
	/*
		（"）もしくは（'）があったら削除
		（"）の場合は展開してから削除
		展開したものをlexerで分割する
	*/
	t_expanser	expanser;
	t_cmd_lst	*now;
	int			debug=0;

	now = cmd->next;
	while (now != cmd)//cmdの中身がNULLまで繰り返す（echo->Hello w$TEST->yootaki）
	{
		/* init */
		expanser.str = now->str;
		expanser.str_cnt = 0;

		while (expanser.str[expanser.str_cnt] != '\0')//\0まで繰り返す（e->c->h->o->\0）
		{
			// printf("%d\n", debug++);
			//------------------------------------------
			//1. 変数を展開
			if (expanser.str[expanser.str_cnt] == '$')
				expansion_var(&expanser, env);
			//2. クォーテーションを削除
			//3. lexer
			//------------------------------------------
			expanser.str_cnt++;
			// printf("%s\n", &expanser.str[expanser.str_cnt]);
		}
		now->str = expanser.str;
		now = now->next;
	}

	return (EXIT_SUCCESS);
}

int	main(void)//想定入力 -> echo "Hello w$TEST yootaki" "Hello w"'orld' "Hello w" 'orld'
{
	t_cmd_lst cmd[6];
	t_envlist env[3];

	cmd[0].prev = &cmd[5];
	cmd[0].next = &cmd[1];
	cmd[0].str = NULL;

	cmd[1].prev = &cmd[0];
	cmd[1].next = &cmd[2];
	cmd[1].str = ft_strdup("echo");

	cmd[2].prev = &cmd[1];
	cmd[2].next = &cmd[3];
	cmd[2].str = ft_strdup("\"Hello w$TEST yootaki\"");

	cmd[3].prev = &cmd[2];
	cmd[3].next = &cmd[4];
	cmd[3].str = ft_strdup("\"Hello w\"\'orld\'");

	cmd[4].prev = &cmd[3];
	cmd[4].next = &cmd[5];
	cmd[4].str = ft_strdup("\"Hello w\"");

	cmd[5].prev = &cmd[4];
	cmd[5].next = &cmd[0];
	cmd[5].str = ft_strdup("\'orld\'");

	env[0].prev = &env[2];
	env[0].next = &env[1];
	env[0].key = NULL;
	env[0].value = NULL;

	env[1].prev = &env[0];
	env[1].next = &env[2];
	env[1].key = "USER";
	env[1].value = "yootaki";

	env[2].prev = &env[1];
	env[2].next = &env[0];
	env[2].key = "TEST";
	env[2].value = "orld";

	printf("展開前 : %s\n", cmd[2].str);
	expanser(&cmd[0], &env[0]);
	printf("展開後 : %s\n", cmd[2].str);
	free(cmd[0].str);
	free(cmd[1].str);
	free(cmd[2].str);
	free(cmd[3].str);
	free(cmd[4].str);
	return (EXIT_SUCCESS);
}

__attribute__((destructor))
void    destructor(void)
{
    int    status;

    status = system("leaks a.out &> leaksout");
    if (status)
    {
        write(2, "leak!!!\n", 8);
        system("cat leaksout >/dev/stderr");
        exit(1);
    }
}
