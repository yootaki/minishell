#include "utils.h"
#include "parse.h"
#include "input.h"

/*void	check(t_nlst *node)
{
	t_nlst	*ncurrent;
	t_cmd_lst *ccurrent;
	t_redirect *rcurrent;

	printf("status = %d\n", node->status);
	ncurrent = node->next;
	printf("ncurrent = %d\n", ncurrent->status);
	while (ncurrent != node)
	{
		ccurrent = node->cmd->next;
		while (ccurrent != node->cmd)
		{
			printf("ccurrent = %s\n", ccurrent->str);
			ccurrent = ccurrent->next;
		}
		rcurrent = node->redirect->next;
		while (rcurrent != node->redirect)
		{
			printf("rcurent = %s\n", rcurrent->str);
			rcurrent = rcurrent->next;
		}
		ncurrent = ncurrent->next;
	}
}*/

int	get_cmdline_from_input_str(char *command)
{
	t_tokeniser	data;
	t_nlst		*node;

	node = init_node();
	if (!node)
		return (EXIT_FAILURE);
	lexer(&data, command); //単語分割
	parse(&node, data.token); //分割したものをlstに入れる
	//check(node);
	return (EXIT_SUCCESS);
}

void	loop_shell(char **envp)
{
	t_envlist *envp_lst;
	char	*command;
	int		start;
	size_t	i;

	envp_lst = get_envp(envp);
	read_history(".my_history");
	i = 0;
	start = 0;
	while (1)
	{
		command = readline("minishell >> ");
		printf("line is '%s'\n", command);
		get_cmdline_from_input_str(command);
		add_history(command);
		free(command);
		write_history(".my_history");
	}
}

int main(int argc, char *argv[], char **envp)
{
	argc = 0;
	argv = NULL;
	loop_shell(envp);
	return (EXIT_SUCCESS);
}