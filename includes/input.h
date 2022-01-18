/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:06:08 by hryuuta           #+#    #+#             */
/*   Updated: 2022/01/18 10:46:49 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdbool.h>
# include "../library/libft/libft.h"
# include "utils.h"
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_status;

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
	CHAR_NULL = '\0',
	HEAR_DOC,
	T_LESSER,
	DLESSER = 64,
	DGREATER = 65,
}		t_token_type;

typedef struct s_token
{
	struct s_token	*next;
	t_token_type	type;
	int				specified_fd;
	char			*str;
}		t_token;

typedef struct s_tokeniser
{
	t_token			*token;
	size_t			cmd_len;
	size_t			char_cnt;
	int				flg;
	int				start;
}				t_tokeniser;

t_token_type	check_type(char *str);

/* ./lexer/is_function.c */
bool			is_type(int c);
void			is_alnum(char **cmd, size_t *char_cnt);
void			is_digit(char **cmd, size_t *char_cnt);
void			is_quort(char **cmd, size_t *char_cnt);
void			is_else(char **cmd, size_t *char_cnt);

/* ./lexer/lst_function.c */
t_token			*lst_new(char *str, int flag);
void			lst_clear(t_token **lst, void (*del)(void*));
t_token			*lst_last(t_token *lst);
void			lstadd_back(t_token **lst, t_token *new_list);

/* ./lexer/init_datas.c */
void			init_data(t_tokeniser *data, char *command);

/* ./lexer/lexer_utils.c */
void			proceed_command(char **cmd, char *ch, size_t *char_cnt);
void			is_specified_fd(t_tokeniser *data, char *command);
void			is_functions(t_tokeniser **data, char **cmd);
void			advance_space(t_tokeniser **data, char **cmd);

/* ./lexer/lexer.c */
int				lexer(t_tokeniser *data, char *command);
int				character_separator(char *command, t_tokeniser *data);
int				sep_command_line(char *command, char *cmd, t_tokeniser *data);
bool			is_delimiter(char *cmd);
int				put_in_list(t_tokeniser *data, char **command, char **cmd);

#endif
