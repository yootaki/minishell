#include "input.h"

void	free_line(void *line)
{
	free(line);
	line = NULL;
}
