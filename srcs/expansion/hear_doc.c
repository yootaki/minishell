#include "../builtin_cmd/builtin_cmd.h"
#include "expansion.h"

enum	e_fd
{
	READ,
	WRITE,
	FD_NUM
};

char	*expansion_hear_doc(char *line, t_envlist *env)
{
	char	*var_name;
	char	*var_value;
	char	*newline;
	char	*tmp;
	int		line_cnt;

	line_cnt = 0;
	while (line[line_cnt] != '$' && line[line_cnt] != '\0')
		line_cnt++;
	if (line[line_cnt] == '\0')
		return (line);
	line[line_cnt] = '\0';
	var_name = get_var_name(&line[line_cnt + 1]);
	var_value = ft_strdup(get_var_value(var_name, env));
	tmp = ft_strjoin(line, var_value);
	newline = ft_strjoin(tmp, &line[line_cnt + ft_strlen(var_name) + 1]);
	free(var_name);
	free(var_value);
	free(tmp);
	return (newline);
}

void	ft_putstr_endl(char *line, int *pipe_fd)
{
	ft_putstr_fd("> ", 1);
	ft_putendl_fd(line, pipe_fd[WRITE]);
}

int	hear_doc(t_redirect *now, t_envlist *env)
{
	int			pipe_fd[FD_NUM];
	char		*expanded_line;
	char		*line;
	char		*separator;
	int			status;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	separator = now->str;
	ft_putstr_fd("> ", 1);
	while (1)
	{
		status = get_next_line(0, &line);
		if (!ft_strncmp(line, separator, ft_strlen(separator) + 1))
			break ;
		expanded_line = expansion_hear_doc(line, env);
		if (status == 1)
			ft_putstr_endl(expanded_line, pipe_fd);
		if (status == 0)
			ft_putstr_fd(expanded_line, pipe_fd[WRITE]);
		free(line);
		if (status == -1)
		{
			perror("malloc");
			return (EXIT_FAILURE);
		}
	}
	free(line);
	now->heardoc_fd = pipe_fd;
	return (EXIT_SUCCESS);
}

//expanded_lineがmallocしてる
int	heardoc_and_redirect(t_redirect *redirect, t_envlist *env)
{
	t_redirect	*now;

	now = redirect->next;
	if (now->str == NULL)
		return (EXIT_SUCCESS);
	while (now != redirect)
	{
		/* fear_doc */
		if (!ft_strncmp(now->str, "<<", ft_strlen(now->str)))
		{
			now = now->next;
			if (now->str == NULL)
				printf("bash: syntax error near unexpected token `newline'\n");
			hear_doc(now, env);
		}

		/* redirect */
		if (!ft_strncmp(now->str, ">", ft_strlen(now->str)))
		{
			now = now->next;
			if (now->str == NULL)
				printf("bash: syntax error near unexpected token `newline'\n");
			now->redirect_fd = open(now->str, O_CREAT | O_TRUNC | O_RDWR, S_IWUSR);
		}
		else if (!ft_strncmp(now->str, ">>", ft_strlen(now->str)))
		{
			now = now->next;
			if (now->str == NULL)
				printf("bash: syntax error near unexpected token `newline'\n");
			now->redirect_fd = open(now->str, O_CREAT | O_APPEND | O_WRONLY, S_IWUSR);
		}
		now = now->next;
	}
	return (EXIT_SUCCESS);
}
