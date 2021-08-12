/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:01:13 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/21 10:49:05 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	str_reverse(char *str)
{
	size_t		i;
	char		temp;
	size_t		len;

	len = ft_strlen(str);
	i = 0;
	while (i < (len / 2))
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
		i++;
	}
}

static	size_t	nbr_count(long num)
{
	size_t	i;

	i = 0;
	while (num > 0)
	{
		i++;
		num /= 10;
	}
	return (i);
}

static	char	*negative_nbr_str(int n)
{
	long	num;
	size_t	len;
	char	*str;
	int		i;

	num = (long)n;
	num = -num;
	len = nbr_count(num);
	str = (char *)malloc(sizeof(char) * (len + 2));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (len--)
	{
		str[i] = num % 10 + '0';
		i++;
		num /= 10;
	}
	str[i] = '-';
	str[i + 1] = '\0';
	str_reverse(str);
	return (str);
}

static	char	*positive_nbr_str(int n)
{
	long	num;
	size_t	len;
	char	*str;
	int		i;

	num = (long)n;
	len = nbr_count(num);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (len--)
	{
		str[i] = num % 10 + '0';
		i++;
		num /= 10;
	}
	str[i] = '\0';
	str_reverse(str);
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;

	if (n == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		if (str == NULL)
			return (NULL);
		str[0] = '0';
		return (str);
	}
	else if (n < 0)
		return (negative_nbr_str(n));
	else
		return (positive_nbr_str(n));
}
