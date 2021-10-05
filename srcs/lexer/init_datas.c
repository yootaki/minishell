/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:02:11 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/05 14:02:13 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/input.h"

void	init_data(t_tokeniser *data, char *command)
{
	data->cmd_len = 0;
	data->cmd_len = ft_strlen(command);
	data->token = NULL;
	data->char_cnt = 0;
	data->flg = 0;
	data->start = 0;
}
