#include "../builtin_cmd/builtin_cmd.h"
#include "expansion.h"

char	*get_var_name(char *str)
{
	char	*var_name;
	int		name_len;

	name_len = 0;
	while (str[name_len] != '\0' && str[name_len] != '$' && str[name_len] != ' ' \
	&& str[name_len] != '\"' && str[name_len] != '\'')
		name_len++;
	var_name = (char *)malloc(sizeof(char) * (++name_len));
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

static void	expansion_var(t_expanser *expanser, t_envlist *env)
{
	char	*var_name;
	char	*var_value;
	char	*new_str;
	char	*tmp;

	expanser->str[expanser->str_cnt] = '\0';
	var_name = get_var_name(&expanser->str[expanser->str_cnt + 1]);
	var_value = ft_strdup(get_var_value(var_name, env));
	tmp = ft_strjoin(expanser->str, var_value);
	new_str = ft_strjoin(tmp, &expanser->str[expanser->str_cnt + ft_strlen(var_name) + 1]);
	expanser->str_cnt += ft_strlen(var_value);
	free(var_name);
	free(var_value);
	free(tmp);
	free(expanser->str);
	expanser->str = new_str;
}

int	categorize(t_cmd_lst *now)
{
	struct stat		buf;

	if (stat(now->str, &buf))
		return (ISSTR);
	if (S_ISREG(buf.st_mode))
		return (ISFILE);
	else if (S_ISDIR(buf.st_mode))
		return (ISDIRECTORY);
	return (ISSTR);
}

//(\")か(\')が見つかったらフラグを立てる。
//もし見つかった際にどちらかのフラグが立っていたらフラグは立てない
//フラグが立っている状態でもう一度見つかったらフラグを取り消す
//(\')だった場合は展開しない！！！
int	expanser(t_cmd_lst *cmd, t_envlist *env)
{
	t_expanser	expanser;
	t_cmd_lst	*now;
	int			add_lst_cnt;

	now = cmd->next;
	while (now != cmd)
	{
		expanser.str = now->str;
		expanser.str_cnt = 0;
		add_lst_cnt = 1;
		//1. 変数を展開
		while (expanser.str[expanser.str_cnt] != '\0')
		{
			if (expanser.str[expanser.str_cnt] == '$')
				expansion_var(&expanser, env);
			else
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
		//3. lexer & categorize
		expanser.str_cnt = 0;
		add_lst_cnt = sep_str(now, &expanser);
		while (--add_lst_cnt >= 0)
		{
			now->category = categorize(now);
			now = now->next;
		}
	}
	return (EXIT_SUCCESS);
}
