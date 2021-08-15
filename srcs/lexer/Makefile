NAME = minishell

#SRCS_DIR = ./input/

SRCS_NAME = main.c\
	is_function.c\
	lst_function.c\
	free_function.c\
	init_datas.c

#SRCS = ${addprefix ${SRCS_DIR}, ${SRCS_NAME}}

HEADER = ../../includes

LIBFT_DIR = ../../libft

OBJS = ${SRCS_NAME:.c=.o}

CC = gcc

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