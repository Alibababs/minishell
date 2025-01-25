GREEN	= \033[1;32m
RED		= \033[0;31m
BLUE	= \033[0;34m
YELLOW	= \033[1;33m
CYAN	= \033[0;36m
RESET	= \033[0m

NAME		=	minishell

CC			=	cc

FLAG		=	-Wall -Werror -Wextra -g3 -fPIE -I./includes

LIBFT_PATH	=	./libft/

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

C_FILE		=	main/main	 									\
				main/signals									\
				main/free										\
				main/error_msg									\
				main/print										\
				env/init_env									\
				lexer/lexer										\
				lexer/lexer_utils								\
				expander/expander								\
				expander/expander_utils							\
				expander/handle_dollar							\
				parsing/parsing									\
				exec/exec										\
				exec/exec_utils									\
				exec/exec_path									\
				exec/exec_argv									\
				exec/exec_utils_bis								\
				exec/exec_hd									\
				exec/exec_redirs								\
				exec/exec_files									\
				exec/exec_bis									\
				builtins/builtin_utils							\
				builtins/echo									\
				builtins/exit									\
				builtins/pwd									\
				builtins/cd 									\
				builtins/env									\
				builtins/export									\
				builtins/unset									\

SRC_DIR		=	./srcs/

SRC			=	$(addsuffix .c, $(addprefix $(SRC_DIR),$(C_FILE)))

OBJ			=	$(SRC:.c=.o)

.c.o:
	@$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

$(LIBFT_LIB):
	@echo "$(BLUE)Compiling $(LIBFT_PATH)...$(RESET)"
	@make -sC $(LIBFT_PATH)
	@echo "$(GREEN)libft.a created$(RESET)"

$(NAME): $(LIBFT_LIB) $(OBJ)
	@echo "$(BLUE)Compiling $(NAME)...$(RESET)"
	@$(CC) $(OBJ) $(LIBFT_LIB) $(FLAG) -lreadline -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created$(RESET)"

clean:
	@echo "$(RED)Deleting object files in $(LIBFT_PATH)...$(RESET)"
	@make clean -sC $(LIBFT_PATH)
	@echo "$(GREEN)Done$(RESET)"
	@echo "$(RED)Deleting $(NAME) object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(GREEN)Done$(RESET)"

fclean: clean
	@echo "$(RED)Deleting $(NAME) executable...$(RESET)"
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_PATH)
	@echo "$(GREEN)Done$(RESET)"

re: fclean all

.PHONY: all clean fclean re
