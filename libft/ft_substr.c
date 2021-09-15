/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 10:09:32 by yootaki           #+#    #+#             */
/*   Updated: 2021/04/24 12:15:10 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			j;
	size_t			s_len;
	char			*ans;

	if (s == NULL)
		return ((void *)0);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	if (len > s_len - (size_t)start)
		len = s_len - (size_t)start;
	ans = (char *)malloc(sizeof(char) * (len + 1));
	if (ans == NULL)
		return ((void *)0);
	i = 0;
	while (i < start)
		i++;
	j = 0;
	while (j < len && s[i] != '\0')
		ans[j++] = s[i++];
	ans[j] = '\0';
	return (ans);
}
