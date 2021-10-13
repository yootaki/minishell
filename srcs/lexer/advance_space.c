/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:21:17 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/13 20:21:34 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/input.h"

void	advance_space(t_tokeniser **data, char **cmd)
{
	while (**cmd == CHAR_WHITESPACE || **cmd == CHAR_TAB)
	{
		(*cmd)++;
		(*data)->start++;
	}
}
