#include "input.h"
/*
* 分割した文字列をft_substr()で作成
* listに作成した文字列を追加
* エラー対応していない
* 17行目仮置き
*/
void	put_in_list(t_tokeniser *data, char **command, char **cmd)
{
	char	*str;
	t_token	*new_list;

	str = ft_substr(*command, data->start, data->char_cnt);
	new_list = lst_new(str);
	if (new_list == NULL)
	{
		lst_clear(&data->token, free_line);
		return ;
	}
	lstadd_back(&data->token, new_list);
	data->start = 0;
	data->char_cnt = 0;
	*command = *cmd;
}

/*
* スペース又はタブの時はスキップ
* [スペース、＜、＞、＜＜、＞＞、｜]を区切り文字として「英字、数字」「数字のみ」「’、”」「その他」に分けて区切る
* エラー未対応
* 39行目　仮置き
*/
void	sep_command_line(char *command, char *cmd, t_tokeniser *data)
{
	while (*cmd == CHAR_WHITESPACE || *cmd == CHAR_TAB)
	{
		cmd++;
		data->start++;
	}
	if (*cmd == '\0')
		return ;
	if (ft_isalpha(*cmd))
		is_alnum(&cmd, &data->char_cnt);
	else if (ft_isdigit(*cmd))
		is_digit(&cmd, &data->char_cnt);
	else if (*cmd == CHAR_QOUTE || *cmd == CHAR_DQUOTE)
		is_quort(&cmd, &data->char_cnt);
	else if (*cmd == CHAR_PIPE || *cmd == CHAR_GREATER || *cmd == CHAR_LESSER)
		is_else(&cmd, &data->char_cnt);
	if (*cmd == CHAR_WHITESPACE || *cmd == '\0' || *cmd == CHAR_PIPE || *cmd == CHAR_LESSER \
	|| *cmd == CHAR_GREATER || ((cmd[-1] == CHAR_PIPE || cmd[-1] == CHAR_LESSER \
	|| cmd[-1] == CHAR_GREATER) && ft_isalnum(*cmd)))
		put_in_list(data, &command, &cmd);
	if (*cmd != '\0')
		sep_command_line(command, cmd, data);
}

void	character_separator(char *command, t_tokeniser *data)
{
	int		i;
	char	*cmd;

	cmd = command;
	i = 0;
	sep_command_line(command, cmd, data);
	while (data->token != NULL)
	{
		printf("data->token->str[%d] = %s\n", i, data->token->str);
		data->token = data->token->next;
		i++;
	}
}

void	lexer_and_parser(char *command)
{
	t_tokeniser	data;

	data.token = NULL;
	init_datas(&data);
	character_separator(command, &data);
	//parse_complete_command(&data.token);
}

int	main(void)
{
	char	*command;
	int		start;
	size_t	i;

	read_history(".my_history");
	i = 0;
	start = 0;
	while (1)
	{
		command = readline("minishell >> ");
		printf("line is '%s'\n", command);
		lexer_and_parser(command);
		add_history(command);
		free(command);
		write_history(".my_history");
	}
	return (0);
}
