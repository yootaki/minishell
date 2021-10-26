/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:05:47 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/26 16:42:23 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../srcs/builtin_cmd/builtin_cmd.h"
# include "input.h"
# include "parse.h"
# include "utils.h"
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

enum e_STD_FD
{
	STD_BACKUP,
	STD_RESTORE,
};

typedef enum e_mode_type
{
	ERROR,
	IS_FILE,
	IS_DIR,
	ELSE_MODE
}	t_mode_type;

enum	e_built
{
	ECHO,
	CD,
	ENV,
	EXPORT,
	PWD,
	UNSET,
	EXIT,
	NO_CMD,
	OTHER
};

typedef struct s_data
{
	char	**path_list;
	char	**cmd_array;
	char	**cmd;
	int		backup_stdout;
	int		backup_stdin;
	int		backup_error;
	t_nlst	*top;
}		t_data;

/* search_cmd.c */
t_mode_type		ft_stat(char *pathname);
char			*strjoin_2times(char *path, char *str, char *cmd);
char			*cmd_path_direct(char *cmd);
char			*cmd_path(char *cmd, t_data *data);
char			*search_cmd(char *cmd, t_data *data);

/* create_cmd_array.c */
int				cmd_lst_len(t_cmd_lst *cmd);
char			**get_cmd_str(t_nlst *node);
char			**create_cmd_array(t_nlst *node, t_data *data);

/* exe_free_function.c */
void			ft_exit(int status);
void			free_path_list(char **path_list);
void			free_function(t_data *data, int pattern);

/* execution_utils1.c */
void			init_execution(t_data *data, t_nlst *node);
int				is_builtin_cmd(char *cmd);

/* execute_command.c */
char			*tolower_cmd(char *cmd);
void			execute_command(t_nlst *node, t_data *data);

/* execution_free.c */
void			free_path_lst(t_data *data);
void			free_data_lst(t_data *data);
void			free_all(char **cmd_array, t_nlst *node, t_data *data);

/* execution.c */
int				backup_std_fd(t_data *data, int mode);
void			no_pipe_and_builtcmd(t_nlst *node, t_data *data);
void			pipe_existence(t_nlst *node, t_data *data);
void			exection(t_nlst *node);
void			close_redirect_fd(t_nlst *node);

/* get_path.c */
char			**search_path(t_envlist	*envp);
int				get_path(t_nlst *node, t_data *data);

/* no_built_cmd.c */
int				check_type_redirect(t_redirect **r_lst, t_data *data);
int				check_std_fd_in_use(int specified_fd, t_data *data);
int				change_fd(t_redirect *r_lst, int redirect_fd, \
int std_fd, t_data *data);
int				check_redirect(t_nlst *node, t_data *data);
void			no_built_cmd(t_nlst *node, t_data *data);

/* process_function.c */
void			ft_call_child(t_nlst *node, t_data *data, \
int prev_read_fd, int *pipefd);
int				ft_call_parent(t_nlst *node, t_data *data, \
int prev_read_fd, int *pipefd);
int				execution_process(t_nlst *node, t_data *data);

#endif
