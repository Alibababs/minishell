/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:01:47 by pbailly           #+#    #+#             */
/*   Updated: 2024/10/02 15:45:35 by phautena         ###   ########.fr       */
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

# define ERROR 1

# define BUILTIN 101
# define REDIR_OUT 102
# define REDIR_IN 103
# define PIPE 104
# define ENVAR 105
# define FILE 106
# define ARGV 107
# define CMD 108

typedef struct	s_cmd
{
	char			**path;
	char			**argv;
	int				pid;
	int				to_read;
	int				to_write;
	int				builtin;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct	s_input
{
	int				env_file;
	char			*input;
	int				*tokenized;
	struct s_cmd	*head_cmd;
}	t_input;

void	ft_signals(void);

///lexer.c>>>
int		lexer(t_input *input);
int		*tokenize(char **splitted);
int		assign_token(char *str, int prev);
int		assign_first_token(char *str);
int		is_argv(int prev);
int		is_file(int prev);
int		is_env(char *str);
int		is_pipe(char *str);
int		is_builtin(char *str);
int		is_redirection(char *str);
char	**declare_builtin(void);

///free.c>>>
void	free_input_struct(t_input *input);
void	free_array(char **array);

#endif
