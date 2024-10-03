/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:01:47 by pbailly           #+#    #+#             */
/*   Updated: 2024/10/03 13:06:12 by phautena         ###   ########.fr       */
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
	PIPE,
	IN,
	OUT,
	HEREDOC,
	APPEND,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	CMD,
	ARGV,
}	t_type;

typedef struct	s_token
{
	t_type			token;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

void	ft_signals(void);

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

#endif
