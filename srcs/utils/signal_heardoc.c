/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heardoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:21 by hryuuta           #+#    #+#             */
/*   Updated: 2022/01/29 00:28:07 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
