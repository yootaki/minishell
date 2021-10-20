/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heardoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:21 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/19 21:14:59 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	redirect_sig_int_input(void)
{
	exit (EXIT_FAILURE);
}

void	redirect_signal_proc(void)
{
	/*
	ctrl + c <- 改行あり終了
	bash-3.2$ cat << end
	>
	bash-3.2$

	ctrl + d <- 改行なし終了
	bash-3.2$ cat << end
	> bash-3.2$
	*/

	// if (signal(SIGINT, redirect_sig_int_input) == SIG_ERR)
	// 	perror("signal");
	// else if (signal(SIGTERM, SIG_IGN) == SIG_ERR)
	// 	perror("signal");
	// else if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	// 	perror("signal");
}
