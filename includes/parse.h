#ifndef PARSE_H
# define PARSE_H

# include "input.h"
# include "utils.h"
# include "../libft/libft.h"
# include <stdbool.h>

enum	e_fd
{
	READ,
	WRITE,
	FD_NUM
};

typedef struct s_cmd_lst
{
	struct	s_cmd_lst	*next;
	struct	s_cmd_lst	*prev;
	t_token_type		c_type;
	int					category;
	int					status;
	char				*str;
}		t_cmd_lst;

typedef struct	s_redirect
{
	struct s_redirect	*next;
	struct s_redirect	*prev;
	t_token_type		c_type;
	int					status;
	int					fd_flag;
	int					spec_fd;
	int					heardoc_fd;
	int					redirect_fd;
	char				*str;
	char				*limmiter;
}		t_redirect;

typedef struct s_nlst
{
	t_cmd_lst	*cmd;
	t_redirect	*redirect;
	t_envlist	*envp_lst;
	struct s_nlst	*next;
	struct s_nlst	*prev;
	int	status;
}		t_nlst;

/* ./parse/free_node.c */
void	free_cmd_lst(t_cmd_lst *cmd);
void	free_redirect_lst(t_redirect *redirect);
void	free_node(t_nlst *node);
void	free_data(t_tokeniser *data);

/* ./parse/create_lst.c */
int	create_cmd_lst(t_cmd_lst *cmd, t_token *tokens);
int	create_redirect_lst(t_redirect *redirect, t_token **tokens);
int	create_node_lst(t_nlst *node, t_token *tokens, t_envlist *env);

/* ./parse/init_lst_function.c */
t_cmd_lst	*init_cmd_lst(void);
t_redirect	*init_redirect(void);
t_nlst	*init_node(void);

/* ./parse/parse_lst_function */
int	cmd_lst_add(t_cmd_lst *nil, t_token *token);
int	redirect_lst_add(t_redirect *nil, t_token *tokens);
int	nlst_add(t_nlst *nil, t_envlist *env_lst);

/* ./parse/parse.c */
bool	is_next_redirect(t_token *tokens);
int	create_lst(t_nlst **n_lst, t_token **tokens);
int	is_type_pipe(t_nlst **n_lst, t_token **tokens);
int	syntax_analysis(t_nlst *node, t_token *tokens);
int	parse(t_nlst *node, t_token *tokens, t_envlist *envp_lst);
int	parse_separator(t_nlst *node, t_token *tokens, t_envlist *env);

#endif
