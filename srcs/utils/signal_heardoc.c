#include "../../includes/utils.h"

void	redirect_sig_int_input()
{
	exit (EXIT_FAILURE);
}

void	redirect_sig_term_input(){}

void	redirect_sig_quit_input()
{
	ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
}

void	redirect_signal_proc()
{
	if (signal(SIGINT, redirect_sig_int_input) == SIG_ERR)
		perror("signal");
	else if (signal(SIGTERM, redirect_sig_term_input) == SIG_ERR)
		perror("signal");
	else if (signal(SIGQUIT, redirect_sig_quit_input) == SIG_ERR)
		perror("signal");
}
