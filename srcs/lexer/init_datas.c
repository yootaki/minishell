#include "../../includes/input.h"

void	init_data(t_tokeniser *data, char *command)
{
	data->cmd_len = 0;
	data->cmd_len = ft_strlen(command);
	data->token = NULL;
	data->char_cnt = 0;
	data->flg = 0;
	data->start = 0;
}
