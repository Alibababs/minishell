NAME = 	libft.a

CC = 	gcc 

FLAGS = -Wall -Wextra -Werror

SRC = 	ft_isalnum.c  ft_isascii.c  ft_isprint.c  ft_memmove.c  ft_strlen.c \
		ft_bzero.c ft_isalpha.c ft_isdigit.c ft_memcpy.c ft_memset.c \
		ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
		ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
		ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
        ft_printf.c ft_printf_hexa.c ft_printf_utils.c \
		get_next_line.c ft_atol.c ft_strcmp.c \

OBJ = ${SRC:.c=.o}

all: 	${NAME}

${NAME}: 	${OBJ}
		ar rc ${NAME} ${OBJ}

.c.o:
		${CC} ${FLAGS} -c $< -o $@

clean:
		rm -f ${OBJ} ${B_OBJ}

fclean: clean
		rm -f ${NAME}

re: 	fclean all

.PHONY: all bonus clean fclean re
