/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:27 by hryuuta           #+#    #+#             */
/*   Updated: 2022/01/18 11:00:14y yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "utils.h"

/* ctrl + C */
void	sig_int_input()
{
	ft_putstr_fd("\b\b  \n", STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/* ctrl + \ */
void	sig_quit_input()
{
	ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
}

void	signal_proc(void)
{
	if (signal(SIGINT, sig_int_input) == SIG_ERR)
	{
		perror("signal");
	}
	if (signal(SIGQUIT, sig_quit_input) == SIG_ERR)
	{
		perror("signal");
	}
	if (signal(SIGTERM, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
	}
}
