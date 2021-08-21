#ifndef PARSE_H
#define PARSE_H

#include "input.h"
#include "libft.h"
#include <stdbool.h>

typedef struct s_cmd_lst
{
	struct	s_cmd_lst	*next;
	struct	s_cmd_lst	*prev;
	t_token_type	c_type;
	int	status;
	char	*str;
}		t_cmd_lst;

typedef struct	s_redirect
{
	struct s_redirect	*next;
	struct s_redirect	*prev;
	int	status;
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
	int	status;
}		t_nlst;

/* ./parse/init_lst_function.c */
t_cmd_lst	*init_cmd_lst(void);
t_redirect	*init_redirect(void);
t_nlst	*init_node(void);

/* ./parse/parse_lst_function */
int	cmd_lst_add(t_cmd_lst *nil, t_token *token);
int	redirect_lst_add(t_redirect *nil, t_token *tokens);
int	nlst_add(t_nlst *nil);

/* ./parse/parse.c */
bool	is_next_redirect(t_token *tokens);
int	create_cmd_lst(t_cmd_lst *cmd, t_token *tokens);
int	create_redirect_lst(t_redirect *redirect, t_token *tokens);
int	parse(t_nlst **node, t_token *tokens);
int	parse_separator(t_nlst **node, t_token *tokens);

#endif
