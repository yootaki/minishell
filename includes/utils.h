/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:06:17 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/23 20:25:49 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>

typedef struct s_envlist
{
	struct s_envlist	*prev;
	struct s_envlist	*next;
	char				*key;
	char				*value;
}		t_envlist;

/* ./utils/envp_lst.c */
t_envlist	*init_envlist(void);
t_envlist	*ft_envlstnew(char *key, char *value);
t_envlist	*init_envlist(void);
void		ft_envlstadd_back(t_envlist *top, t_envlist *new_lst);
int			ft_envlstsize(t_envlist *lst);
void		free_envplist(t_envlist *nil);

/* ./utils/get_envp.c */
t_envlist	*get_envp(char **envp);
int			envp_lstmap(t_envlist *envp, char *key, char *value);
int			create_envlst(t_envlist *lst, char **envp);

/* signal_main.c */
void		signal_proc(void);

/* signal_heardoc.c */
void		heardoc_signal_proc(void);

/* wrapper_1.c */
void		xclose(int fd);
int			xdup2(int oldfd, int newfd);
int			xdup(int oldfd);

/* wrapper_2.c */
char		*ft_xstrdup(char *s);
char		*ft_xstrjoin(char *s1, char *s2);
char		*ft_xsubstr(char const *s, unsigned int start, size_t len);
char		**ft_xsplit(char const *s, char c);
char		*ft_xitoa(int n);

/* wrapper_3.c */
void		xwaitpid(pid_t pid, int *wstatus, int options);
void		xpipe(int *pipefd);
pid_t		xfork(void);

#endif
