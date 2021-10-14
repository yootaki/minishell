/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:27 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/14 03:48:46 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	sig_int_input()
{
	ft_putstr_fd("\b\b  \b\n", STDERR_FILENO);
	ft_putstr_fd("minishell >> ", STDERR_FILENO);
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
