#ifndef EXECUTION_H
#define EXECUTION_H

#include "../srcs/builtin_cmd/builtin_cmd.h"
#include "input.h"
#include "parse.h"
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct s_data
{
	char	**path_list;
	char	**cmd_array;
	char	**cmd;
	int	backup_stdout;
	int	backup_stdin;
	int	backup_error;
	t_nlst	*top;
}		t_data;

/* cmd_lst_len.c */
int	cmd_lst_len(t_cmd_lst *cmd);
char	**get_cmd_str(t_nlst *node);
char	*strjoin_2times(char *path, const char *str, char *cmd);
char	*search_cmd(char *cmd, t_data *data);
char	**create_cmd_array(t_nlst *node, t_data *data);
void	free_function(t_data *data, int pattern);

/* execution.c */
int	exection(t_nlst *node);
int	exec_builtin(t_nlst *node);

/* execution_free.c */
void	free_path_lst(t_data *data);
void	free_data_lst(t_data *data);
void	free_all(char **cmd_array, t_nlst *node, t_data *data);

/* execution_process.c */
//void	ft_call_child(t_nlst *node, t_data *data, int *pipefd);
void	check_redirect(t_nlst *node);
void	no_built_cmd(t_nlst *node, t_data *data);
void	execute_command(t_nlst *node, t_data *data);
void	ft_call_child(t_nlst *node, t_data *data, int prev_read_fd, int *pipefd);
int	ft_call_parent(t_nlst *node, t_data *data, int prev_read_fd, int *pipefd);
int	execution_process(t_nlst *node, t_data *data);

/* get_path.c */
char	**search_path(t_envlist	*envp);
int	get_path(t_nlst *node, t_data *data);


#endif
