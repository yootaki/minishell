/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:27 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/18 22:57:45 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	sig_int_input(void)
{
	ft_putstr_fd("\b\b  \b\n", STDERR_FILENO);
	ft_putstr_fd("minishell >> ", STDERR_FILENO);
}

void	sig_term_input(void)
{
}

void	sig_quit_input(void)
{
	ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
}

void	signal_proc(void)
{
	if (signal(SIGINT, sig_int_input) == SIG_ERR)
		perror("signal");
	else if (signal(SIGTERM, sig_term_input) == SIG_ERR)
		perror("signal");
	else if (signal(SIGQUIT, sig_quit_input) == SIG_ERR)
		perror("signal");
}

void	signal_ign(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		perror("signal");
	else if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
}
