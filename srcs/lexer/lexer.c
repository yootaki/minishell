#include "input.h"

t_token_type	check_type(char *str)
{
	int	size;

	size = ft_strlen(str);
	if (*str == CHAR_PIPE)
		return (CHAR_PIPE);
	if (*str == CHAR_QOUTE)
		return (CHAR_QOUTE);
	if (*str == CHAR_DQUOTE)
		return (CHAR_DQUOTE);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (DLESSER);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (HEAR_DOC);
	if (*str == CHAR_GREATER)
		return (CHAR_GREATER);
	if (*str == CHAR_LESSER)
		return (CHAR_LESSER);
	return (CHAR_GENERAL);
}
/*
* 分割した文字列をft_substr()で作成
* listに作成した文字列を追加
* エラー対応していない
* 17行目仮置き
*/
int	put_in_list(t_tokeniser *data, char **command, char **cmd)
{
	char	*str;
	t_token	*new_list;

	str = ft_substr(*command, data->start, data->char_cnt);
	if (str == NULL)
	{
		lst_clear(&data->token, free_line);
		return (EXIT_FAILURE);
	}
	new_list = lst_new(str);
	if (new_list == NULL)
	{
		lst_clear(&data->token, free_line);
		return (EXIT_FAILURE);
	}
	lstadd_back(&data->token, new_list);
	data->start = 0;
	data->char_cnt = 0;
	*command = *cmd;
	return (EXIT_SUCCESS);
}

/*
* スペース又はタブの時はスキップ
* [スペース、＜、＞、＜＜、＞＞、｜]を区切り文字として「英字、数字」「数字のみ」「’、”」「その他」に分けて区切る
* エラー未対応
* 39行目　仮置き
*/
int	sep_command_line(char *command, char *cmd, t_tokeniser *data)
{
	while (*cmd == CHAR_WHITESPACE || *cmd == CHAR_TAB)
	{
		cmd++;
		data->start++;
	}
	if (*cmd == '\0')
		return (EXIT_SUCCESS);
	if (ft_isalpha(*cmd) || is_type(*cmd))
		is_alnum(&cmd, &data->char_cnt);
	else if (ft_isdigit(*cmd) || is_type(*cmd))
		is_digit(&cmd, &data->char_cnt);
	else if (*cmd == CHAR_QOUTE || *cmd == CHAR_DQUOTE)
		is_quort(&cmd, &data->char_cnt);
	else if (*cmd == CHAR_PIPE || *cmd == CHAR_GREATER || *cmd == CHAR_LESSER)
		is_else(&cmd, &data->char_cnt);
	if (*cmd == CHAR_WHITESPACE || *cmd == '\0' || *cmd == CHAR_PIPE || *cmd == CHAR_LESSER \
	|| *cmd == CHAR_GREATER || ((cmd[-1] == CHAR_PIPE || cmd[-1] == CHAR_LESSER \
	|| cmd[-1] == CHAR_GREATER) && ft_isalnum(*cmd)))
		if (put_in_list(data, &command, &cmd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (*cmd != '\0')
		sep_command_line(command, cmd, data);
	return (EXIT_SUCCESS);
}

int	character_separator(char *command, t_tokeniser *data)
{
	char	*cmd;

	cmd = command;
	if (sep_command_line(command, cmd, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	lexer(t_tokeniser *data, char *command)
{
	init_data(data);
	if (character_separator(command, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
