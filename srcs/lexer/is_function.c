#include "input.h"

bool	is_type(int c)
{
	if ( c == '$' || c == '.' || c == '/' || c == '-' || c == '?')
		return (true);
	return (false);
}

void	is_alnum(char **cmd, size_t *char_cnt)
{
	while ((ft_isalnum(**cmd) || is_type(**cmd)) && **cmd != '\0')
	{
		(*cmd)++;
		(*char_cnt)++;
	}
}

void	is_digit(char **cmd, size_t *char_cnt)
{
	while ((ft_isdigit(**cmd) || is_type(**cmd)) && **cmd != '\0')
	{
		(*cmd)++;
		(*char_cnt)++;
	}
}

void	is_quort(char **cmd, size_t *char_cnt)
{
	char	ch;

	ch = **cmd;
	(*cmd)++;
	(*char_cnt)++;
	while (**cmd != ch && **cmd != '\0')
	{
		(*cmd)++;
		(*char_cnt)++;
	}
	(*cmd)++;
	(*char_cnt)++;
	if (**cmd == CHAR_QOUTE || **cmd == CHAR_DQUOTE)
	{
		ch = **cmd;
		(*cmd)++;
		(*char_cnt)++;
		while (**cmd != ch && **cmd != '\0')
		{
			(*cmd)++;
			(*char_cnt)++;
		}
		(*cmd)++;
		(*char_cnt)++;
	}
}

void	is_else(char **cmd, size_t *char_cnt)
{
	char	ch;

	if (**cmd == CHAR_GREATER || **cmd == CHAR_LESSER)
	{
		ch = **cmd;
		(*cmd)++;
		(*char_cnt)++;
		if (**cmd == ch)
		{
			(*cmd)++;
			(*char_cnt)++;
		}
	}
	else
	{
		(*cmd)++;
		(*char_cnt)++;
	}
}
