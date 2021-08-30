#include "builtin_cmd.h"
#include "../../includes/input.h"
#include "../../includes/parse.h"
#include "../../includes/utils.h"

int	echo(t_cmd_lst *cmd)
{
	t_cmd_lst	*now;
	int			display_return;

	now = cmd->next->next;
	display_return = 1;
	if (now->str == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	if (!ft_strncmp(now->str, "-n", ft_strlen(now->str)))
	{
		display_return = 0;
		now = now->next;
	}
	while (now != cmd)
	{
		ft_putstr_fd (now->str, STDOUT_FILENO);
		now = now->next;
		if (now != cmd)
			write(STDOUT_FILENO, " ", 1);
	}
	if (display_return)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
