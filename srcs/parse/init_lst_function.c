/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:02:52 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/23 20:42:43 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/expansion.h"

t_cmd_lst	*init_cmd_lst(void)
{
	t_cmd_lst	*new;

	new = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	if (!new)
		exit (print_error_func("malloc"));
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

	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new)
		exit (print_error_func("malloc"));
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

	new = (t_nlst *)malloc(sizeof(t_nlst));
	if (!new)
		exit (print_error_func("malloc"));
	new->next = new;
	new->prev = new;
	return (new);
}
