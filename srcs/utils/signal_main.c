#include "../../includes/utils.h"

void	sig_int_input()
{
	ft_putstr_fd("\b\b  \b\n", STDERR_FILENO);
	ft_putstr_fd("minishell >> ", STDERR_FILENO);
	// exit(1);//無限ループ脱出用
}

void	sig_term_input(){}

void	sig_quit_input()
{
	ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
}

void	signal_proc()
{
	if (signal(SIGINT, sig_int_input) == SIG_ERR)
		perror("signal");
	else if (signal(SIGTERM, sig_term_input) == SIG_ERR)
		perror("signal");
	else if (signal(SIGQUIT, sig_quit_input) == SIG_ERR)
		perror("signal");
}

void	signal_ign()
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		perror("signal");
	else if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
}
