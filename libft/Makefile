# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phautena <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 14:09:23 by phautena          #+#    #+#              #
#    Updated: 2024/05/28 16:10:15 by phautena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
       ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
       ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
       ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
       ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
       ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \

OBJS = ${SRCS:.c=.o}

BSRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BOBJS = ${BSRCS:.c=.o}

COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -c -I.
RM = rm -f

NAME = libft.a

all: ${NAME}

${NAME}:
	${COMPILER} ${CFLAGS} ${SRCS}
	ar rc ${NAME} ${OBJS}

bonus: ${NAME}
	${COMPILER} ${CFLAGS} ${BSRCS}
	ar r ${NAME} ${BOBJS}

clean:
	${RM} ${OBJS} ${BOBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
