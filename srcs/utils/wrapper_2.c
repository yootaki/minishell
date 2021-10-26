/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:32 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/23 20:23:49 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"
#include "../../includes/expansion.h"

char	*ft_xstrdup(char *s)
{
	char	*str;

	str = ft_strdup(s);
	if (!str)
		exit(print_error_func("malloc"));
	return (str);
}

char	*ft_xstrjoin(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (!str)
		exit(print_error_func("malloc"));
	return (str);
}

char	*ft_xsubstr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	str = ft_substr(s, start, len);
	if (!str)
		exit(print_error_func("malloc"));
	return (str);
}

char	**ft_xsplit(char const *s, char c)
{
	char	**str;

	str = ft_split(s, c);
	if (!str)
		exit(print_error_func("malloc"));
	return (str);
}

char	*ft_xitoa(int n)
{
	char	*str;

	str = ft_itoa(n);
	if (str == NULL)
		exit(print_error_func("malloc"));
	return (str);
}
