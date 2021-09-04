#include "expansion.h"

void	delete_dquote(t_expanser *expanser)
{
	char	*str_front;
	char	*str_middle;
	char	*str_back;
	char	*new_str;
	char	*tmp;

	expanser->str[expanser->str_cnt] = '\0';
	if (expanser->str_cnt > 0)
		str_front = expanser->str;
	else
		str_front = "$";
	expanser->str_cnt++;
	str_middle = &expanser->str[expanser->str_cnt];
	while (expanser->str[expanser->str_cnt] != '\"')
		expanser->str_cnt++;
	expanser->str[expanser->str_cnt] = '\0';
	if (expanser->str[expanser->str_cnt + 1] != '\0')
		str_back = &expanser->str[expanser->str_cnt + 1];
	else
		str_back = "$";
	tmp = ft_strjoin(str_front, str_middle);
	new_str = ft_strjoin(tmp, str_back);
	free(tmp);
	free(expanser->str);
	expanser->str = new_str;
	expanser->str_cnt -= 2;
}

void	delete_quote(t_expanser *expanser)
{
	char	*str_front;
	char	*str_middle;
	char	*str_back;
	char	*new_str;
	char	*tmp;

	expanser->str[expanser->str_cnt] = '\0';
	if (expanser->str_cnt > 0)
		str_front = expanser->str;
	else
		str_front = "$";
	expanser->str_cnt++;
	str_middle = &expanser->str[expanser->str_cnt];
	while (expanser->str[expanser->str_cnt] != '\'')
		expanser->str_cnt++;
	expanser->str[expanser->str_cnt] = '\0';
	if (expanser->str[expanser->str_cnt + 1] != '\0')
		str_back = &expanser->str[expanser->str_cnt + 1];
	else
		str_back = "$";
	tmp = ft_strjoin(str_front, str_middle);
	new_str = ft_strjoin(tmp, str_back);
	free(tmp);
	free(expanser->str);
	expanser->str = new_str;
	expanser->str_cnt--;
}
