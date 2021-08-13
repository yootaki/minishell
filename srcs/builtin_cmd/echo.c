#include "../../libft/libft.h"

/* compile command */
/* $ gcc -o myecho echo.c ../../libft/libft.a */

int	main(int argc, char **argv)
{
	int	display_return;

	display_return = 1;
	if (argc < 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
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
