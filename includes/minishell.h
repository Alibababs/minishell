/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:01:47 by pbailly           #+#    #+#             */
/*   Updated: 2024/10/03 14:39:12 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define ERROR 1
# define SUCCESS 0

typedef enum
{
	PIPE = 101,
	IN = 102,
	OUT = 103,
	HEREDOC = 104,
	APPEND = 105,
	S_QUOTE = 106,
	D_QUOTE = 107,
	CMD = 108,
	ARGV = 109,
	BUILTIN = 110,
	ENV = 111,
	FIL = 112,
	NDEF = 113,
}	t_type;

typedef struct	s_token
{
	t_type			token;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

void	ft_signals(void);

///free.c>>>
void	free_array(char **array);

///lexer.c>>>
int		lexer(char *input);
void	tokenize_all(char *input, t_token **head);
void	tokenize_char(int *i_ptr, char *input, t_token **head);
void	tokenize_str(int *i_ptr, char *input, t_token **head);
int		is_sep(char c);
void	tokenize_quote(int *i_ptr, char *input, t_token **head, int mode);

///lexer_list.c>>>
void	add_token_end(char *to_tokenize, t_token **head);
void	add_token_empty(char *to_tokenize, t_token **head);
void	print_token(t_token **head);

///lexer_fix_redir.c>>>
void	fix_redir_list(t_token **head);
void	fix_redir(t_token **start);
void	del_next_redir(t_token **current);
void	add_redir(t_token **current);
int		is_redir(char *value);

///lexer_is_token.c
int		is_in(char *str);
int		is_out(char *str);
int		is_append(char *str);
int		is_hd(char *str);
int		is_pipe(char *str);

///lexer_is_token_bis.c
int		is_argv(t_type prev);
int		is_squote(char *str);
int		is_dquote(char *str);
int		is_builtin(char *str);
char	**declare_builtin(void);

///lexer_is_cmd.c
char	**get_path(void);
char	**fix_env(char **env);
int		is_cmd(char *str);
int		is_env(char *str);
int		is_file(char *str);

///lexer_assign_token.c
void	tokenize(t_token **head);
void	assign_token(t_token **current);
void	assign_token_bis(t_token **current);

#endif
