# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phautena <phautena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 12:30:36 by phautena          #+#    #+#              #
#    Updated: 2024/08/01 12:32:19 by phautena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = get_next_line.c get_next_line_utils.c

OBJS = ${SRCS:.c=.o}

COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -c -I.
RM = rm -f

NAME = gnl.a

all: ${NAME}

${NAME}:
	${COMPILER} ${CFLAGS} ${SRCS}
	ar rc ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
