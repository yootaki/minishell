#include "input.h"

typedef	enum	e_tokentype
{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_WHITESPACE = ' ',
	CHAR_DGREATER = '>>',
	CHAR_DLESSER = '<<',
	CHAR_TAB = '\t',
	CHAR_ESCAPE = '\\',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
}		t_token_type;

typedef struct	s_token
{
	t_token	next;
	t_token_type	type;
	char	*str;
}		t_token;

typedef struct	s_tokeniser
{
	t_token			token;
	size_t	char_cnt;
	int	start;
}				t_tokeniser;

t_token	*ft_lstnew(char *c, char *s)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = c;
	token->next = NULL;
	token->str = s;
	return (token);
}

void	init_token(t_token *token)
{
	token->next = NULL;
	token->type = 0;
	token->str = NULL;
}

void	init_data(t_tokeniser *data)
{
	data->char_cnt = 0;
	data->start = 0;
}

void	is_alnum(char **cmd, size_t *char_cnt)
{
	while (ft_isalnum(**cmd) && **cmd != '\0')
	{
		(*cmd)++;
		(*char_cnt)++;
	}
}

void	is_digit(char **cmd, size_t *char_cnt)
{
	while ((ft_isdigit(**cmd) || **cmd == '.') && **cmd != '\0')
	{
		(*cmd)++;
		(*char_cnt)++;
	}
}

void	is_quort(char **cmd, size_t *char_cnt)
{
	char	ch;

	ch = **cmd;
	(*cmd)++;
	(*char_cnt)++;
	while (**cmd != ch && **cmd != '\0')
	{
		(*cmd)++;
		(*char_cnt)++;
	}
	(*cmd)++;
	(*char_cnt)++;
	if (**cmd == '\'' || **cmd == '\"')
	{
		ch = **cmd;
		(*cmd)++;
		(*char_cnt)++;
		while (**cmd != ch && **cmd != '\0')
		{
			(*cmd)++;
			(*char_cnt)++;
		}
		(*cmd)++;
		(*char_cnt)++;
	}
}

void	is_else(char **cmd, size_t *char_cnt)
{
	char	ch;

	if (**cmd == '>' || **cmd == '<')
	{
		ch = **cmd;
		(*cmd)++;
		(*char_cnt)++;
		if (**cmd == ch)
		{
			(*cmd)++;
			(*char_cnt)++;
		}
	}
	else
	{
		(*cmd)++;
		(*char_cnt)++;
	}
}

void	put_in_list(t_tokeniser *data, char **command, char **cmd)
{
	printf("char_cnt = %zu\n", data->char_cnt);
	str[s] = ft_substr(command, data->start, data->char_cnt);
	data->start = 0;
	data->char_cnt = 0;
	*command = *cmd;
	printf("str = %s\n", str[s]);
}

/*
* スペース又はタブの時はスキップ
* [スペース、＜、＞、＜＜、＞＞、｜]を区切り文字として「英字、数字」「数字のみ」「’、”」「その他」に分けて区切る
*/

void	sep_command_line(char *command, char *cmd, t_tokeniser *data)
{
	char *str; //とりあえず

	while (*cmd == ' ' || *cmd == '\t')
	{
		cmd++;
		data->start++;
	}
	if(*cmd == '\0') /* バッファが空 */
		return ;
	if (ft_isalpha(*cmd))
		is_alnum(&cmd, &data->char_cnt);
	else if (ft_isdigit(*cmd))
		is_digit(&cmd, &data->char_cnt);
	else if (*cmd == '\'' || *cmd == '\"')
		is_quort(&cmd, &data->char_cnt);
	else if (*cmd == '|' || *cmd == '>' || *cmd == '<')
		is_else(&cmd, &data->char_cnt);
	int s = 0;
	if (*cmd == ' ' || *cmd == '\0' || *cmd == '|' || *cmd == '<' || *cmd == '>'
	|| ((cmd[-1] == '|' || cmd[-1] == '<' || cmd[-1] == '>') && ft_isalnum(*cmd)))
	{
		printf("char_cnt = %zu\n", data->char_cnt);
		str = ft_substr(command, data->start, data->char_cnt);
		data->start = 0;
		data->char_cnt = 0;
		command = cmd;
		printf("str = %s\n", str[s]);
		s++;
	}
	if (*cmd != '\0')
		sep_command_line(command, cmd, data);
}

void	character_separator(char *command, t_tokeniser *data)
{
	size_t	i;
	int	start;
	char	*cmd;

	cmd = command;
	i = 0;
	start = 0;
	sep_command_line(command, cmd, data);
}

void	init_datas(t_tokeniser *data)
{
	init_data(data);
	init_token(&data->token);
}

void	lexer(char *command)
{
	t_tokeniser data;

	init_datas(&data);
	character_separator(command, &data);
}

int	main()
{
	char	*command;
	int	start;
	size_t	i;

	read_history(".my_history");
	i = 0;
	start = 0;
	while(1)
	{
		command = readline("minishell >> ");
		printf("line is '%s'\n", command);
		lexer(command);
		add_history(command);
		free(command);
		write_history(".my_history");
	}
	return (0);
}
