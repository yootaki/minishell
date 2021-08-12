# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/03 10:40:37 by hryuuta           #+#    #+#              #
#    Updated: 2021/04/24 16:28:52 by hryuuta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c\
	  ft_bzero.c\
	  ft_calloc.c\
	  ft_isascii.c\
	  ft_isalnum.c\
	  ft_isdigit.c\
	  ft_isalpha.c\
	  ft_isprint.c\
	  ft_itoa.c\
	  ft_memccpy.c\
	  ft_memchr.c\
	  ft_memmove.c\
	  ft_memcmp.c\
	  ft_memcpy.c\
	  ft_memset.c\
	  ft_putchar_fd.c\
	  ft_putendl_fd.c\
	  ft_putnbr_fd.c\
	  ft_putstr_fd.c\
	  ft_split.c\
	  ft_strnstr.c\
	  ft_strchr.c\
	  ft_strlcat.c\
	  ft_strlcpy.c\
	  ft_strlen.c\
	  ft_strmapi.c\
	  ft_strncmp.c\
	  ft_strrchr.c\
	  ft_strjoin.c\
	  ft_strdup.c\
	  ft_strtrim.c\
	  ft_substr.c\
	  ft_tolower.c\
	  ft_toupper.c

BONUS_SRCS = ft_lstnew.c\
			 ft_lstadd_front.c\
			 ft_lstsize.c\
			 ft_lstsize.c\
			 ft_lstlast.c\
			 ft_lstadd_back.c\
			 ft_lstdelone.c\
			 ft_lstclear.c\
			 ft_lstiter.c\
			 ft_lstmap.c
	   
REG_OBJS = $(SRCS:%.c=%.o)

BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)

CC = gcc

CFLAGS = -Wextra -Werror -Wall

RM = rm -f


.c.o:
	$(CC) $(CFLAGS) -c $< -I libft.h


all:	$(NAME)

bonus:	$(BONUS_OBJS) $(REG_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS) $(REG_OBJS)

$(NAME):	$(REG_OBJS)
			 ar rc $(NAME) $(REG_OBJS)

clean: 
	$(RM) $(REG_OBJS) $(BONUS_OBJS)
fclean:		clean
	$(RM) $(NAME)

re:		fclean all

.PHONY:	all	clean fclean re bonus
