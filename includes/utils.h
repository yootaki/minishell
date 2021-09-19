#ifndef UTILS_H
# define UTILS_H

# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdbool.h>
#include <string.h>
# include <errno.h>

typedef struct	s_envlist
{
	struct s_envlist	*prev;
	struct s_envlist	*next;
	char				*key;
	char				*value;
}		t_envlist;

/* ./utils/envp_lst.c */
t_envlist	*init_envlist(void);
t_envlist	*ft_envlstnew(char *key, char *value);
void		ft_init_envlst(t_envlist *lst);
void		ft_envlstadd_back(t_envlist *top, t_envlist *new_lst);
int			ft_envlstsize(t_envlist *lst);
void		free_envplist(t_envlist *nil);

/* ./utils/get_envp.c */
int		envp_lstmap(t_envlist *envp, char *key, char *value);
int		create_envlst(t_envlist *lst, char **envp);
t_envlist	*get_envp(char **envp);

/* signal_main.c */
void	sig_int_input();
void	sig_term_input();
void	sig_quit_input();
void	signal_proc();
void	signal_ign();

/* signal_heardoc.c */
void	redirect_sig_int_input();
void	redirect_sig_term_input();
void	redirect_sig_quit_input();
void	redirect_signal_proc();

/* x_funtion.c */
void	xclose(int fd);
int	xdup2(int oldfd, int newfd);
int	xdup(int oldfd);

/* x_function2.c */
void	xwaitpid(pid_t pid, int *wstatus, int options);
void	xpipe(int *pipefd);
pid_t	xfork(void);

#endif
