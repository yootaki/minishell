#ifndef INPUT_H
# define INPUT_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"

/*
* HEAR_DOC = '>>'
* DLESSER = '<<'
*/

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

typedef struct s_token
{
	struct s_token	*next;
	t_token_type	type;
	char			*str;
}		t_token;

typedef struct s_tokeniser
{
	t_token			*token;
	size_t			char_cnt;
	int				start;
}				t_tokeniser;

/* ./lexer/is_function.c */
void	is_alnum(char **cmd, size_t *char_cnt);
void	is_digit(char **cmd, size_t *char_cnt);
void	is_quort(char **cmd, size_t *char_cnt);
void	is_else(char **cmd, size_t *char_cnt);

/* ./lexer/lst_function.c */
t_token	*lst_new(char *str);
void	lst_clear (t_token **lst, void (*del)(void*));
t_token	*lst_last(t_token *lst);
void	lstadd_back(t_token **lst, t_token *new_list);

/* ./lexer/init_datas.c */
void	init_data(t_tokeniser *data);
void	init_datas(t_tokeniser *data);

/* ./lexer/free_function.c */
void	free_line(void *line);

/* ./lexer/lexer.c */
int		lexer(t_tokeniser *data, char *command);
void	character_separator(char *command, t_tokeniser *data);
void	sep_command_line(char *command, char *cmd, t_tokeniser *data);
t_token_type	check_type(char *str);

#endif
