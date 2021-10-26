/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:27 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/20 16:38:21 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	signal_proc(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		perror("signal");
	else if (signal(SIGTERM, SIG_IGN) == SIG_ERR)
		perror("signal");
	else if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
}
