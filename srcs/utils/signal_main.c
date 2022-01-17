/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:27 by hryuuta           #+#    #+#             */
/*   Updated: 2022/01/17 15:25:58 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* ctrl + C */
void	sig_int_input()
{
	// \bは1文字分カーソルを左にずらしている
	// MINISHELLはutils.hで定義している。（"minishell >> "）
	ft_putstr_fd("\b\b  \b\n", STDERR_FILENO);
	ft_putstr_fd(MINISHELL, STDERR_FILENO);
}

/* ctrl + \ */
void	sig_quit_input()
{
	ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
}

void	signal_proc(void)
{
	if (signal(SIGINT, sig_int_input) == SIG_ERR)
		perror("signal");
	else if (signal(SIGTERM, SIG_IGN) == SIG_ERR)
		perror("signal");
	else if (signal(SIGQUIT, sig_quit_input) == SIG_ERR)
		perror("signal");
}
