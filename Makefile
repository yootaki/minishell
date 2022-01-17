NAME = minishell
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -I ${HEADER} -I ${LIBFT_DIR}
HEADER = ./includes
LIBFT_DIR = ./library/libft

BUILTIN_DIR = ./srcs/builtin_cmd/
EXECUTION_DIR = ./srcs/execution/
EXPANSION_DIR = ./srcs/expansion/
LEXER_DIR = ./srcs/lexer/
PARSER_DIR = ./srcs/parse/
UTILS_DIR = ./srcs/utils/

SRCS_BUILTIN = cd.c echo.c env.c exit.c export.c export_utils.c pwd.c unset.c
SRCS_EXECUTION = create_cmd_array.c exe_free_function.c execution_utils1.c execute_command.c execution_free.c execution.c get_path.c no_built_cmd.c process_function.c search_cmd.c
SRCS_EXPANSION = expansion.c delete_quote.c separate_str.c heardoc_and_redirect.c heardoc.c redirect.c expansion_utils1.c expansion_utils2.c pipe_next_cmd_check.c pipe_next_cmd_check_utils.c
SRCS_LEXER = lexer.c is_function.c lexer_utils.c advance_space.c
SRCS_PARSER = parse.c parse_utils.c parse_lst_function.c create_lst.c
SRCS_UTILS = envlst_func.c get_envp.c signal_main.c signal_heardoc.c wrapper_1.c wrapper_2.c wrapper_3.c ft_atol.c malloc_and_strlcpy.c init.c free_func.c lst_func.c

SRCS_B = ${addprefix ${BUILTIN_DIR}, ${SRCS_BUILTIN}}
SRCS_EXEC = ${addprefix ${EXECUTION_DIR}, ${SRCS_EXECUTION}}
SRCS_E = ${addprefix ${EXPANSION_DIR}, ${SRCS_EXPANSION}}
SRCS_L = ${addprefix ${LEXER_DIR}, ${SRCS_LEXER}}
SRCS_P = ${addprefix ${PARSER_DIR}, ${SRCS_PARSER}}
SRCS_U = ${addprefix ${UTILS_DIR}, ${SRCS_UTILS}}

SRCS_NAME = ./srcs/main.c ${SRCS_L} ${SRCS_P} ${SRCS_E} ${SRCS_B} ${SRCS_U} ${SRCS_EXEC} ./library/get_next_line/get_next_line.c ./library/get_next_line/get_next_line_utils.c

OBJS = ${SRCS_NAME:.c=.o}

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

debug: CFLAGS += -g3 -fsanitize=address
debug: re

check:
	@cd testcase && bash check.sh

.PHONY: all clean fclean re
