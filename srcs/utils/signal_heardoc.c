/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heardoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:21 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/20 16:40:45 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	heardoc_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
}

void	heardoc_signal_proc(void)
{
	if (signal(SIGINT, &heardoc_signal_handler) == SIG_ERR)
		perror("signal");
	else if (signal(SIGTERM, &heardoc_signal_handler) == SIG_ERR)
		perror("signal");
	else if (signal(SIGQUIT, &heardoc_signal_handler) == SIG_ERR)
		perror("signal");
}
