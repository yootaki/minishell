NAME = minishell

LEXER_DIR = ./srcs/lexer/

PARSER_DIR = ./srcs/parse/

BUILTIN_DIR = ./srcs/builtin_cmd/

UTILS_DIR = ./srcs/utils/

SRCS_LEXER = lexer.c is_function.c lst_function.c free_function.c init_datas.c

SRCS_PARSER = parse.c init_lst_function.c parse_lst_function.c create_lst.c free_node.c

SRCS_BUILTIN = cd.c echo.c env.c exit.c export.c lst_func.c pwd.c unset.c

SRCS_UTILS = envp_lst.c get_envp.c

SRCS_L = ${addprefix ${LEXER_DIR}, ${SRCS_LEXER}}

SRCS_P = ${addprefix ${PARSER_DIR}, ${SRCS_PARSER}}

SRCS_B = ${addprefix ${BUILTIN_DIR}, ${SRCS_BUILTIN}}

SRCS_U = ${addprefix ${UTILS_DIR}, ${SRCS_UTILS}}

SRCS_NAME = ./srcs/main.c ${SRCS_L} ${SRCS_P} ${SRCS_B} ${SRCS_U} ./srcs/expansion/expansion.c ./srcs/exection/exection.c

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
