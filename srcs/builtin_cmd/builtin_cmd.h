/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:42:04 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/10 19:56:18 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CMD_H
# define BUILTIN_CMD_H

# include "../../libft/libft.h"
# include "../../includes/input.h"
# include "../../includes/parse.h"
# include "../../includes/utils.h"
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

extern int	g_status;

int		my_echo(t_cmd_lst *cmd);
int		my_cd(t_cmd_lst *cmd, t_envlist *envp_lst);
int		my_env(t_envlist *envp_lst);
int		my_export(t_cmd_lst *cmd, t_envlist *envp_lst);
int		my_pwd(t_envlist *envp_lst);
int		my_unset(t_cmd_lst *cmd, t_envlist *envp_lst);
int		my_exit(t_cmd_lst *cmd);

/* util function */
char	*malloc_and_copy(char *str, int size);
void	ft_envlstdelone(t_envlist *lst);
void	free_envlst(t_envlist *lst);

long	ft_atol(const char *str);

#endif
