#include "input.h"
#include "parse.h"
#include "utils.h"

/*void	check_env(t_envlist *envp)
{
	int i = 0;
	t_envlist	*e_tmp;
	i = 0;
	e_tmp = envp->next;
	while (e_tmp != envp)
	{
		printf("e_value[%d] = %s\n", i, e_tmp->value);
		printf("e_key[%d] = %s\n", i, e_tmp->key);
		e_tmp = e_tmp->next;
		i++;
	}
}*/

void	check(t_nlst *nil)
{
	int i = 0;
	t_nlst	*current;
	t_cmd_lst *c_tmp;
	t_redirect	*r_tmp;
	t_envlist	*e_tmp;

	current = nil->next;
	while (current != nil)
	{
		i = 0;
		c_tmp = current->cmd->next;
		while (c_tmp != current->cmd)
		{
			printf("c_str = %s\n", c_tmp->str);
			c_tmp = c_tmp->next;
			i++;
		}
		i = 0;
		r_tmp = current->redirect->next;
		while (r_tmp != current->redirect)
		{
			printf("r_str = %s\n", r_tmp->str);
			r_tmp = r_tmp->next;
			i++;
		}
		i = 0;
		e_tmp = current->envp_lst->next;
		while (e_tmp != current->envp_lst)
		{
			printf("e_value[%d] = %s\n", i, e_tmp->value);
			printf("e_key[%d] = %s\n", i, e_tmp->key);
			e_tmp = e_tmp->next;
			i++;
		}
		current = current->next;
	}
}

t_nlst	*get_cmdline_from_input_str(char *command, t_envlist *envp_lst)
{
	t_tokeniser	data;
	t_nlst		*node;

	node = init_node();
	if (!node)
		return (NULL);
	lexer(&data, command); //単語分割
	if (data.token == NULL)
		return (NULL);
	parse(node, data.token, envp_lst); //分割したものをlstに入れる
	check(node);
	// free_data(&data);
	// free_node(node);
	return (node);
}

int	expanser(t_cmd_lst *cmd, t_envlist *env);

void	loop_shell(char **envp)
{
	t_nlst		*node;
	t_envlist *envp_lst;
	char	*command;
	int		start;
	size_t	i;

	envp_lst = get_envp(envp);
	read_history(".my_history");
	i = 0;
	start = 0;
	while (i < 1)
	{
		command = readline("minishell >> ");
		if (command[0] != '\0')
			node = get_cmdline_from_input_str(command, envp_lst);

		//expanser
		expanser(node->next->cmd, envp_lst);

		t_cmd_lst *tmp;
		tmp = node->next->cmd->next;
		printf("after  : ");
		for (size_t i = 1; i < 11; i++)
		{
			printf("%s", tmp->str);
			if (i < 10)
				printf(" ");
			else
				printf("\n");
			tmp = tmp->next;
		}

		add_history(command);
		free(command);
		write_history(".my_history");
		i++;
	}
	free_envplist(envp_lst);
}

int main(int argc, char *argv[], char **envp)
{
	argc = 0;
	argv = NULL;
	loop_shell(envp);
	//free(envp);
	// system("leaks minishell");
	return (EXIT_SUCCESS);
}
