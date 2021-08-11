NAME = input

SRCS_DIR = ./input/

SRCS_NAME = main.c

SRCS = ${addprefix ${SRCS_DIR}, ${SRCS_NAME}}

HEADER = ./includes

LIBFT_DIR = ./LIBFT_DIR

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I ${HEADER} -I {LIBFT_DIR}

RM = rm -rf

MAKE_BONUS = make bonus

all: ${NAME}

${NAME}: ${OBJS} ${HEADER} ${LIBFT_DIR}
	@${MAKE_BONUS} -C ${LIBFT_DIR}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L ${LIBFT_DIR} -lft

clean:
	${MAKE} -C ${LIBFT_DIR} clean
	${RM} ${OBJS}

fclean: clean
	${MAKE} -C ${LIBFT_DIR} fclean
	${RM} ${NAME}