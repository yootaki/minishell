#include "input.h"

void	command_line_sep(char *command)
{
	char	**cmd;

	cmd = ft_split(command, ' ');
	int i = 0;
	while (cmd[i] != NULL)
	{
		printf("cmd[%d] = %s\n", i, cmd[i]);
		i++;
	}
}

int	main()
{
	char	*command;

	//init_list(argc, argv);
	//lexcial(argc, argv);
	using_history();
	read_history(".my_history");
	while(1)
	{
		command = readline("minishell >> ");
		printf("line is '%s'\n", command);
		command_line_sep(command);
		add_history(command);
		free(command);
		write_history(".my_history");
	}
	return (0);
}
