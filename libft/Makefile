NAME = 	libft.a

CC = 	gcc

FLAGS = -Wall -Wextra -Werror -ggdb

C_FILE =	ft_printf			\
			ft_printf_hexa		\
			ft_printf_utils		\
			get_next_line		\
			ft_isalnum			\
			ft_isascii			\
			ft_isprint			\
			ft_memmove			\
			ft_strlen			\
			ft_bzero			\
			ft_isalpha			\
			ft_isdigit			\
			ft_memcpy			\
			ft_memset			\
			ft_strlcpy			\
			ft_strlcat			\
			ft_toupper			\
			ft_tolower			\
			ft_strchr			\
			ft_strrchr			\
			ft_strncmp			\
			ft_memchr			\
			ft_memcmp			\
			ft_strnstr			\
			ft_atoi				\
			ft_calloc			\
			ft_strdup			\
			ft_substr			\
			ft_strjoin			\
			ft_strtrim			\
			ft_split			\
			ft_itoa				\
			ft_strmapi			\
			ft_striteri			\
			ft_putchar_fd		\
			ft_putstr_fd		\
			ft_putendl_fd		\
			ft_putnbr_fd		\
			ft_atol				\
			ft_strcmp			\
			ft_tablen			\
			ft_isspace			\
			ft_isalpha_lower	\
			ft_isalpha_upper	\
			ft_strncpy			\
			ft_strstr			\
			ft_strcat			\
			ft_strcpy			\
			ft_strtok			\

SRCS = $(addsuffix .c,$(C_FILE))

OBJ = ${SRCS:.c=.o}

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
