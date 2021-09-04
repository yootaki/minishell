#ifndef BUILTIN_CMD_H
#define BUILTIN_CMD_H

#include "../libft/libft.h"
#include "input.h"
#include "parse.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

# define CURRENTPATH_SIZE 512

t_envlist	*ft_envlstnew(char *key, char *value);
void		ft_envlstdelone(t_envlist *lst);
void		ft_envlstadd_back(t_envlist *top, t_envlist *new);
int			ft_envlstsize(t_envlist *lst);
void		free_envlst(t_envlist *lst);

/* cd.c */
int	cd(t_cmd_lst *cmd, t_envlist *envp_lst);
/* echo.c */
int	echo(t_cmd_lst *cmd);
/* env.c */
int	env(t_envlist *envp_lst);
/* export.c */
int	export(t_cmd_lst *cmd, t_envlist *envp_lst);
/* pwd.c */
int	my_pwd(t_envlist *lst);
/* unset.c */
int	my_unset(char **argv, t_envlist *lst);


#endif
