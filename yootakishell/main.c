#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MYSH_RL_BUFSIZE 1024
char	*mysh_read_line(void)
{
	int		bufsize = MYSH_RL_BUFSIZE;
	int		position = 0;
	char	*buffer = malloc(sizeof(char) * bufsize);
	int		c;

	if (!buffer)
	{
		fprintf(stderr, "mysh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		//read a character
		c = getchar();

		//if hit EOF, replace it with a null char and return
		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
		{
			buffer[position] = c;
		}
		position++;

		//if we have exeeded the buffer, reallocate
		if (position >= bufsize)
		{
			bufsize += MYSH_RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				fprintf(stderr, "mysh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

#define MYSH_TOK_BUFSIZE 64
#define MYSH_TOK_DELIM " \t\r\n\a"
char	**mysh_split_line(char *line)
{
	int		bufsize = MYSH_TOK_BUFSIZE;
	int		position = 0;
	char	**tokens = malloc(sizeof(char*) * bufsize);
	char	*token;

	if (!tokens)
	{
		fprintf(stderr, "mysh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, MYSH_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += MYSH_TOK_BUFSIZE;
			tokens = realloc(tokens, sizeof(char*) * bufsize);
			if (!tokens)
			{
				fprintf(stderr, "mysh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, MYSH_TOK_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}

int	mysh_launch(char **args)
{
	__pid_t	pid;
	__pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0)//child
	{
		if (execvp(args[0], args) == -1)
			perror("mysh");
		exit (EXIT_FAILURE);
	}
	else if (pid < 0)//error
		perror("mysh");
	else//parent
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}


// ========================================================================
/* Function Declarations for builtin shell commands */
int	mysh_cd(char **args);
int	mysh_help(char **args);
int	mysh_exit(char **args);

/* List of builtin commands, followed by their corresponding functions */
char	*builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int	(*builtin_func[])(char**) = {
	&mysh_cd,
	&mysh_help,
	&mysh_exit
};

int	mysh_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char*);
}

int	mysh_cd(char **args)
{
	if (args[1] == NULL)
		fprintf(stderr, "mysh: expected argument to \"cd\"\n");
	else
	{
		if (chdir(args[1]) != 0)
			perror("mysh");
	}
	return (1);
}

int	mysh_help(char **args)
{
	int	i;

	printf("Stephen Brennan's LSH\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");
	for (i = 0; i < mysh_num_builtins(); i++)
		printf(" %s\n", builtin_str[i]);
	printf("Use the man command for information on other programs.\n");
	return (1);
}

int	mysh_exit(char **args)
{
	return (0);
}

// ========================================================================

int	mysh_execute(char **args)
{
	int	i;

	if (args[0] == NULL)
		return (1);

	for (i = 0; i < mysh_num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(args);
	}

	return mysh_launch(args);
}

void	mysh_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	do {
		printf("> ");
		//read
		line = mysh_read_line();
		//lexer, parser
		args = mysh_split_line(line);
		//execute
		status = mysh_execute(args);

		free(line);
		free(args);
	} while(status);
}

int	main(int argc, char **argv)
{

	mysh_loop();

	return (EXIT_SUCCESS);
}
