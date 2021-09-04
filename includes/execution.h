#ifndef EXECUTION_H
#define EXECUTION_H

#include "builtin_cmd.h"
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
	int	backup_stdout;
}		t_data;

enum	e_fd
{
	READ,
	WRITE,
	FD_NUM
};

/* cmd_lst_len.c */
int	cmd_lst_len(t_cmd_lst *cmd);
char	**get_cmd_str(t_nlst *node);
char	*strjoin_2times(char *path, const char *str, char *cmd);
char	*search_cmd(char *cmd, t_data *data);
char	**create_cmd_array(t_nlst *node, t_data *data);

/* execution.c */
int	exection(t_nlst *node);

/* execution_free.c */
void	free_path_lst(t_data *data);
void	free_data_lst(t_data *data);
void	free_all(char **cmd_array, t_nlst *node, t_data *data);

/* execution_process.c */
void	ft_call_child(t_nlst *node, t_data *data, t_nlst *nil, int *pipefd);
int	execution_process(t_nlst *node, t_data *data);

/* get_path.c */
char	**search_path(t_envlist	*envp);
int	get_path(t_nlst *node, t_data *data);


#endif
