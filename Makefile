# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/30 11:30:32 by p0ulp1            #+#    #+#              #
#    Updated: 2024/11/30 12:29:10 by p0ulp1           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc

FLAG		=	-Wall -Werror -Wextra -g3 -fPIE -I./includes

LIBFT_PATH	=	./libft/

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

GNL_PATH	=	./get_next_line/

GNL_FILE	=	gnl.a

GNL_LIB		=	$(addprefix $(GNL_PATH), $(GNL_FILE))

C_FILE		=	main/main	 									\
				main/signals									\
				main/free										\
				main/print										\
				env/init_env									\
				env/env_list									\

SRC_DIR		=	./srcs/

SRC			=	$(addsuffix .c, $(addprefix $(SRC_DIR),$(C_FILE)))

OBJ			=	$(SRC:.c=.o)

.c.o:
	@$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

$(LIBFT_LIB):
	@echo "COMPILING $(LIBFT_PATH)\n"
	@make -sC $(LIBFT_PATH)
	@echo "libft.a created\n"

$(GNL_LIB):
	@echo "COMPILING $(GNL_PATH)\n"
	@make -sC $(GNL_PATH)
	@echo "gnl.a created\n"

$(NAME): $(LIBFT_LIB) $(GNL_LIB) $(OBJ)
	@echo "COMPILING $(NAME)...\n"
	@$(CC) $(OBJ) $(LIBFT_LIB) $(FLAG) -lreadline -o $(NAME)
	@echo "./$(NAME) created\n"

clean:
	@echo "\nDeleting obj file in $(LIBFT_PATH)...\n"
	@make clean -sC $(LIBFT_PATH)
	@echo "Done\n"
	@echo "Deleting $(NAME) object...\n"
	@rm -f $(OBJ)
	@echo "Done\n"

fclean: clean
	@echo "Deleting $(NAME) executable...\n"
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_PATH)
	@echo "Done\n"

re: fclean all

.PHONY: all clean fclean re
