/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 02:30:45 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/21 05:17:50 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	f;

	f = 1;
	if (n < 0)
	{
		f = -1;
		ft_putchar_fd('-', fd);
	}
	if (n < 10 && n > -10)
	{
		ft_putchar_fd('0' + n * f, fd);
	}
	else
	{
		ft_putnbr_fd(n / 10 * f, fd);
		ft_putchar_fd('0' + n % 10 * f, fd);
	}
}
