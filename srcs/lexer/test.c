#include "../../libft/libft.h"

int main(int argc, char *argv[], char **envp)
{
	char	*str;
	char **tmp;
	char	*key[200];
	char	*value[200];
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	tmp = envp;
	while (*envp != NULL)
	{
		printf("--------------------------------\n");
		str = *envp;
		printf("*envp = %s\n", *envp);
		while (*str != '=')
			str++;
		*str = '\0';
		//printf("*envp = %s\n", *envp);
		key[x] = ft_strdup(*envp);
		printf("key[%d] = %s\n", x, key[x]);
		str++;
		//printf("str = %s\n", str);
		value[y] = ft_strdup(str);
		printf("value[%d] = %s\n", y, value[y]);
		printf("--------------------------------\n");
		printf("\n");
		x++;
		y++;
		(envp)++;
	}
	//printf("------------\n");
	/*x = 0;
	y = 0;
	while (key[x] != NULL && value[y] != NULL && *tmp != NULL)
	{
		printf("--------------------------------\n");
		printf("*tmp = %s\n", *tmp);
		printf("key[%d] = %s\n", x, key[x]);
		printf("value[%d] = %s\n", y, value[y]);
		printf("--------------------------------\n");
		printf("\n");
		x++;
		y++;
		tmp++;
	}*/
	return (0);
}