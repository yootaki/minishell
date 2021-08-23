#include "utils.h"
#include "parse.h"
#include "input.h"

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

void	free_node(t_nlst *nil)
{
	printf("-------free_node_start-----\n");
	t_nlst	*n_lst;
	t_nlst	*current;
	t_cmd_lst *c_tmp;
	t_cmd_lst *c_lst;
	t_redirect	*r_tmp;
	t_redirect	*r_lst;
	t_envlist	*e_tmp;
	t_envlist	*e_lst;
	int i = 0;
	int cnt = 0;

	n_lst = nil->next;
	while (n_lst != nil)
	{
		current = n_lst->next;
		c_lst = n_lst->cmd->next;
		i = 0;
		while (c_lst != n_lst->cmd)
		{
			c_tmp = c_lst->next;
			printf("c_str[%d] = %s\n", i, c_lst->str);
			free(c_lst->str);
			c_lst->str = NULL;
			free(c_lst);
			c_lst = NULL;
			c_lst = c_tmp;
			i++;
		}
		r_lst = n_lst->redirect->next;
		i = 0;
		while (r_lst != n_lst->redirect)
		{
			r_tmp = r_lst->next;
			printf("r_str[%d] = %s\n", i, r_lst->str);
			free(r_lst->str);
			r_lst->str = NULL;
			free(r_lst);
			r_lst = NULL;
			r_lst = r_tmp;
			i++;
		}
		e_lst = n_lst->envp_lst->next;
		i = 0;
		while (e_lst != n_lst->envp_lst && cnt == 0)
		{
			e_tmp = e_lst->next;
			printf("e_value[%d] = %s\n", i, e_lst->value);
			printf("e_key[%d] = %s\n", i, e_lst->key);
			free(e_lst->key);
			free(e_lst->value);
			e_lst->key = NULL;
			e_lst->value = NULL;
			free(e_lst);
			e_lst = NULL;
			e_lst = e_tmp;
			i++;
		}
		cnt++;
		free(n_lst);
		n_lst = NULL;
		n_lst = current;
	}
	printf("-------free_node_end-----\n");
}

int	get_cmdline_from_input_str(char *command, t_envlist *envp_lst)
{
	t_tokeniser	data;
	t_nlst		*node;

	node = init_node();
	if (!node)
		return (EXIT_FAILURE);
	lexer(&data, command); //単語分割
	if (data.token == NULL)
		return (EXIT_FAILURE);
	parse(node, data.token, envp_lst); //分割したものをlstに入れる
	check(node);
	free_node(node);
	return (EXIT_SUCCESS);
}

void	loop_shell(char **envp)
{
	t_envlist *envp_lst;
	char	*command;
	int		start;
	size_t	i;

	envp_lst = get_envp(envp);
	//check_env(envp_lst);
	read_history(".my_history");
	i = 0;
	start = 0;
	while (i < 1)
	{
		command = readline("minishell >> ");
		printf("line is '%s'\n", command);
		get_cmdline_from_input_str(command, envp_lst);
		add_history(command);
		free(command);
		write_history(".my_history");
		i++;
	}
}

int main(int argc, char *argv[], char **envp)
{
	argc = 0;
	argv = NULL;
	loop_shell(envp);
	system("leaks minishell");
	return (EXIT_SUCCESS);
}