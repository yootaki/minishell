/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:21:17 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/05 13:45:45 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	advance_space(t_tokeniser **data, char **cmd)
{
	while (**cmd == CHAR_WHITESPACE || **cmd == CHAR_TAB)
	{
		(*cmd)++;
		(*data)->start++;
	}
}
