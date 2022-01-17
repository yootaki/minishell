/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:02:52 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/05 13:54:35 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "expansion.h"

t_cmd_lst	*init_cmd_lst(void)
{
	t_cmd_lst	*new;

	new = (t_cmd_lst *)xmalloc(sizeof(t_cmd_lst));
	new->next = new;
	new->prev = new;
	new->c_type = 0;
	new->category = 0;
	new->status = 0;
	new->str = NULL;
	return (new);
}

t_redirect	*init_redirect(void)
{
	t_redirect	*new;

	new = (t_redirect *)xmalloc(sizeof(t_redirect));
	new->next = new;
	new->prev = new;
	new->str = NULL;
	new->c_type = 0;
	new->spec_flg = 0;
	new->spec_fd = -1;
	new->heardoc_fd = -1;
	new->redirect_fd = -1;
	new->limmiter = NULL;
	new->status = 0;
	return (new);
}

t_nlst	*init_node(void)
{
	t_nlst	*new;

	new = (t_nlst *)xmalloc(sizeof(t_nlst));
	new->next = new;
	new->prev = new;
	return (new);
}

void	init_data(t_tokeniser *data, char *command)
{
	data->cmd_len = 0;
	data->cmd_len = ft_strlen(command);
	data->token = NULL;
	data->char_cnt = 0;
	data->flg = 0;
	data->start = 0;
}
