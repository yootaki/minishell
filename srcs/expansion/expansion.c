#include "../builtin_cmd/builtin_cmd.h"
#include "expansion.h"

//[expansion]=================================================================================
char	*get_var_name(char *str)
{
	char	*var_name;
	int		name_len;

	name_len = 0;
	//ここの条件もう少し考えるべき
	while (str[name_len] != '\0' && str[name_len] != '$' && str[name_len] != ' ' && str[name_len] != '\"' && str[name_len] != '\'')
		name_len++;
	var_name = (char*)malloc(sizeof(char) * (++name_len));
	ft_strlcpy(var_name, str, name_len);
	return (var_name);
}

char	*get_var_value(char *str, t_envlist *env)
{
	t_envlist	*now;

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

	//'$'->'\0' & 変数名を取得
	expanser->str[expanser->str_cnt] = '\0';
	var_name = get_var_name(&expanser->str[expanser->str_cnt + 1]);
	//変数の値を取得
	var_value = ft_strdup(get_var_value(var_name, env));
	//"Hello w\0"とvar_valueをjoin
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
//============================================================================================

//[delete quote]==============================================================================
void	delete_dquote(t_expanser *expanser)
{
	char	*str_front;
	char	*str_middle;
	char	*str_back;
	char	*new_str;
	char	*tmp;

	// '\"'より前
	expanser->str[expanser->str_cnt] = '\0';
	if (expanser->str_cnt > 0)
		str_front = expanser->str;
	else
		str_front = "$";//ダブルクォートを置換えてるの！！！！！

	// '\"' と '\"' の間
	expanser->str_cnt++;
	str_middle = &expanser->str[expanser->str_cnt];
	while (expanser->str[expanser->str_cnt] != '\"')
		expanser->str_cnt++;
	expanser->str[expanser->str_cnt] = '\0';

	// '\"'より後
	if (expanser->str[expanser->str_cnt + 1] != '\0')
		str_back = &expanser->str[expanser->str_cnt + 1];
	else
		str_back = "$";

	tmp = ft_strjoin(str_front, str_middle);
	new_str = ft_strjoin(tmp, str_back);
	free(tmp);
	free(expanser->str);
	expanser->str = new_str;
	expanser->str_cnt -= 2;
}

void	delete_quote(t_expanser *expanser)
{
	char	*str_front;
	char	*str_middle;
	char	*str_back;
	char	*new_str;
	char	*tmp;

	// '\"'より前
	expanser->str[expanser->str_cnt] = '\0';
	if (expanser->str_cnt > 0)
		str_front = expanser->str;
	else
		str_front = "$";

	// '\'' と '\'' の間
	expanser->str_cnt++;
	str_middle = &expanser->str[expanser->str_cnt];
	while (expanser->str[expanser->str_cnt] != '\'')
		expanser->str_cnt++;
	expanser->str[expanser->str_cnt] = '\0';

	// '\"'より後
	if (expanser->str[expanser->str_cnt + 1] != '\0')
		str_back = &expanser->str[expanser->str_cnt + 1];
	else
		str_back = "$";

	tmp = ft_strjoin(str_front, str_middle);
	new_str = ft_strjoin(tmp, str_back);
	free(tmp);
	free(expanser->str);
	expanser->str = new_str;
	expanser->str_cnt--;
}
//============================================================================================

//[lexer]=====================================================================================
void	add_cmd_lst(t_cmd_lst *now)
{
	t_cmd_lst	*newlst;

	newlst = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	newlst->prev = now;
	newlst->next = now->next;
	now->next->prev = newlst;
	now->next = newlst;
}

int	sep_str(t_cmd_lst *now, t_expanser *expanser)
{
	char	*extract_str;
	int		start;
	int		end;
	int		count;

	count = 0;
	while (1)
	{
		while (expanser->str[expanser->str_cnt] == '$')
			expanser->str_cnt++;
		if (expanser->str[expanser->str_cnt] == '\0')
			return (count);
		start = expanser->str_cnt;
		while (expanser->str[expanser->str_cnt] != '\0' && expanser->str[expanser->str_cnt] != '$')
			expanser->str_cnt++;
		end = expanser->str_cnt;

		extract_str = ft_substr(expanser->str, start, end - start);

		if (count == 0)//1つ目なら、now->strに入れる
			now->str = extract_str;
		else//2つ目以降なら、新しいt_cmd_lstを作成、nowとnow->nextの間に挿入、nowを更新
		{
			add_cmd_lst(now);
			now = now->next;
			now->str = extract_str;
		}
		count++;
	}
}
//============================================================================================

//[categorize]================================================================================
int	categorize(t_cmd_lst *now)
{
	struct stat		buf;

	//dirpディレクトリの情報を取得
	if (stat(now->str, &buf))
	{
		printf("%s is str\n", now->str);
		return (ISSTR);
	}
	//fileかdirectoryか判別
	if (S_ISREG(buf.st_mode))
	{
		printf("%s is file\n", now->str);
		return (ISFILE);
	}
	else if (S_ISDIR(buf.st_mode))
	{
		printf("%s is dir\n", now->str);
		return (ISDIRECTORY);
	}
	return (ISSTR);
}
//============================================================================================

int	expanser(t_cmd_lst *cmd, t_envlist *env)
{
	t_expanser	expanser;
	t_cmd_lst	*now;
	int			add_lst_cnt;

	now = cmd->next;
	while (now != cmd)
	{
		/* init */
		expanser.str = now->str;
		expanser.str_cnt = 0;
		add_lst_cnt = 1;

		//1. 変数を展開
		while (expanser.str[expanser.str_cnt] != '\0')
		{
			if (expanser.str[expanser.str_cnt] == '$')
				expansion_var(&expanser, env);
			expanser.str_cnt++;
		}

		//2. クォーテーションを削除
		expanser.str_cnt = 0;
		while (expanser.str[expanser.str_cnt] != '\0')
		{
			if (expanser.str[expanser.str_cnt] == '\"')
				delete_dquote(&expanser);
			else if (expanser.str[expanser.str_cnt] == '\'')
				delete_quote(&expanser);
			expanser.str_cnt++;
		}

		//3. lexer
		expanser.str_cnt = 0;
		add_lst_cnt = sep_str(now, &expanser);

		while (--add_lst_cnt >= 0)
		{
			now->category = categorize(now);//文字列かファイルかディレクトリかを判別
			printf("[debug] category : %d\n", now->category);
			now = now->next;
		}
	}

	return (EXIT_SUCCESS);
}
