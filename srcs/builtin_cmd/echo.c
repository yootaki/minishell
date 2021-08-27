#include "builtin_cmd.h"

int	my_echo(int argc, char **argv)
{
	int	display_return;

	display_return = 1;
	if (argc < 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	argc--;
	argv++;
	if (!ft_strncmp(argv[0], "-n", ft_strlen(argv[0])))
	{
		display_return = 0;
		argc--;
		argv++;
	}
	while (argc > 0)
	{
		ft_putstr_fd (argv[0], STDOUT_FILENO);
		argc--;
		argv++;
		if (argc > 0)
			write(STDOUT_FILENO, " ", 1);
	}
	if (display_return)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	my_echo(argc, argv);
	return (EXIT_SUCCESS);
}
