NAME = minishell

LEXER_DIR = ./srcs/lexer/

PARSER_DIR = ./srcs/parse/

EXPANSION_DIR = ./srcs/expansion/

BUILTIN_DIR = ./srcs/builtin_cmd/

EXECUTION_DIR = ./srcs/execution/

UTILS_DIR = ./srcs/utils/

SRCS_LEXER = lexer.c is_function.c lst_function.c free_function.c init_datas.c

SRCS_PARSER = parse.c init_lst_function.c parse_lst_function.c create_lst.c free_node.c

SRCS_EXPANSION = expansion.c hear_doc.c delete_quote.c sepalate_str.c

SRCS_BUILTIN = cd.c echo.c env.c exit.c export.c lst_func.c pwd.c unset.c

SRCS_EXECUTION = execution.c create_cmd_array.c execution_free.c execution_process.c get_path.c

SRCS_UTILS = envp_lst.c get_envp.c

SRCS_L = ${addprefix ${LEXER_DIR}, ${SRCS_LEXER}}

SRCS_P = ${addprefix ${PARSER_DIR}, ${SRCS_PARSER}}

SRCS_E = ${addprefix ${EXPANSION_DIR}, ${SRCS_EXPANSION}}

SRCS_B = ${addprefix ${BUILTIN_DIR}, ${SRCS_BUILTIN}}

SRCS_EXEC = ${addprefix ${EXECUTION_DIR}, ${SRCS_EXECUTION}}

SRCS_U = ${addprefix ${UTILS_DIR}, ${SRCS_UTILS}}

SRCS_NAME = ./srcs/main.c ${SRCS_L} ${SRCS_P} ${SRCS_E} ${SRCS_B} ${SRCS_U} ${SRCS_EXEC} ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c srcs/exection/exec_builtin.c

HEADER = ./includes

LIBFT_DIR = ./libft

OBJS = ${SRCS_NAME:.c=.o}

CC = gcc -g -fsanitize=address

# -g -fsanitize=address

CFLAGS = -Wall -Wextra -Werror -I ${HEADER} -I ${LIBFT_DIR}

RM = rm -rf

MAKE_BONUS = make bonus

all: ${NAME}

${NAME}: ${OBJS} ${HEADER} ${LIBFT_DIR}
	@${MAKE_BONUS} -C ${LIBFT_DIR}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L ${LIBFT_DIR} -lft -lreadline

clean:
	${MAKE} -C ${LIBFT_DIR} clean
	${RM} ${OBJS}

fclean: clean
	${MAKE} -C ${LIBFT_DIR} fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
