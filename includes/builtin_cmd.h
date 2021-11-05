/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:42:04 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/05 14:20:35 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CMD_H
# define BUILTIN_CMD_H

# include "../library/libft/libft.h"
# include "input.h"
# include "parse.h"
# include "utils.h"
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

/* export utils */
void	swap_envlst(t_envlist *now, t_envlist *min);
void	ft_sort_envlst(t_envlist *nil, int size);
void	sort_and_print_env(t_envlist *envp_lst);
int		get_key_and_value(t_cmd_lst *now, char **key, char **val, int cnt);
int		insert_key_and_value(t_cmd_lst *now, t_envlist *envp_lst);

/* util function */
void	ft_envlstdelone(t_envlist *lst);
void	free_envlst(t_envlist *lst);

long	ft_atol(const char *str);
char	*malloc_and_strlcpy(char *str, int size);

#endif
