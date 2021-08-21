# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>

int main(int argc, char *argv[], char **envp)
{
	char	*command;
	int		start;
	size_t	i;

	read_history(".my_history");
	i = 0;
	start = 0;
	while (1)
	{
		command = readline("minishell >> ");
		printf("line is '%s'\n", command);
		//lexer_and_parser(command);
		add_history(command);
		free(command);
		write_history(".my_history");
	}
	printf("------------\n");
	return (EXIT_SUCCESS);
}