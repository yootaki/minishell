#include "input.h"

/*typedef	enum	e_tokentype
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
}		t_token_type;

typedef struct	s_token
{
	t_token	next;
	t_token_type	type;
	char	*str;
}		t_token;

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
}*/

/*
* スペース又はタブの時はスキップ
* [スペース、＜、＞、＜＜、＞＞、｜]を区切り文字として「英字、数字」「数字のみ」「’、”」「その他」に分けて区切る
*/

void	command_line_sep(char *command, size_t *i, int *start)
{
	//int	start;
	//size_t	i;
	char	*cmd;
	char *str[4];
	char	ch;

	cmd = command;
	//start = 0;
	//i = 0;
	while (*cmd == ' ' || *cmd == '\t')
	{
		cmd++;
		(*start)++;
	}
	if(*cmd == '\0') /* バッファが空 */
		return ;
	if (ft_isalpha(*cmd))
	{
		while (ft_isalnum(*cmd) && *cmd != '\0')
		{
			cmd++;
			(*i)++;
		}
	}
	else if (ft_isdigit(*cmd))
	{
		while ((ft_isdigit(*cmd) || *cmd == '.') && *cmd != '\0')
		{
			cmd++;
			(*i)++;
		}
	}
	else if (*cmd == '\'' || *cmd == '\"')
	{
		ch = *cmd;
		cmd++;
		(*i)++;
		while (*cmd != ch && *cmd != '\0')
		{
			cmd++;
			(*i)++;
		}
		cmd++;
		(*i)++;
		if (*cmd == '\'' || *cmd == '\"')
		{
			ch = *cmd;
			cmd++;
			(*i)++;
			while (*cmd != ch && *cmd != '\0')
			{
				cmd++;
				(*i)++;
			}
			cmd++;
			(*i)++;
		}
	}
	else
	{
			cmd++;
			(*i)++;
	}
	int s = 0;
	printf("---------\n");
	printf("cmd = %c\n", *cmd);
	if (*cmd == ' ' || *cmd == '\0')
	{
		printf("-----if----\n");
		str[s] = ft_substr(command, *start, *i);
		*start = 0;
		*i = 0;
	}
	printf("i = %zu\n", *i);
	printf("start = %d\n", *start);
	printf("cmd = %s\n", cmd);
	printf("str = %s\n", str[s]);
	s++;
	printf("command = %s\n", command);
	printf("---------\n");
	if (*cmd != '\0')
		command_line_sep(cmd, i, start);
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
		command_line_sep(command, &i, &start);
		add_history(command);
		free(command);
		write_history(".my_history");
	}
	return (0);
}
