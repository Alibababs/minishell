/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:38:51 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/09 16:52:38 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern int				g_exit_status;

typedef struct s_data	t_data;

typedef enum s_type
{
	WORD,
	REDIR,
	PIPE,
	QUOTES,
}						t_type;

typedef struct s_token
{
	t_type				token;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
	t_data				*data;
}						t_token;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
	t_data				*data;
}						t_env;

typedef struct s_cmd
{
	char				*path;
	char				**argv;
	int					*infiles;
	int					*outfiles;
	int					nb_infiles;
	int					nb_outfiles;
	int					to_read;
	int					to_write;
	int					pid;
	bool				here_doc;
	t_data				*data;
}						t_cmd;

typedef struct s_data
{
	t_env				*h_env;
	t_token				*h_tokens;
	t_cmd				*h_cmds;
	char				**envp;
	char				*str;
	struct s_data		*next;
}						t_data;

////////////////MAIN/////////////
/// signals.c
void					ft_signals(int mode);
/// free.c
void					ft_error(t_data **data, char *msg);
void					mem_error(t_data **data);
void					mem_error_tokens(t_token **h_tokens);
void					free_env(t_data **data);
void					free_data(t_data **data);
/// print.c
void					print_env(t_data **data);
void					print_tokens(t_token *data);

/////////////ENV/////////////////
/// env_list.c
void					add_env_end(char *name, char *value, t_data **data);
/// init_env.c
void					init_env(t_data **data, char *envp[]);
char					*parse_env_name(char *var);
char					*parse_env_value(char *var);

/////////////LEXER///////////////
/// lexer.c
void					lexer(t_token **h_tokens, char *input);
/// lexer_utils.c
int						is_sep(char c);
int						is_quote(char c);
bool					quotes_closed(char *input);
/////////////EXPANDER/////////////
/// expander.c
void					expander(t_token **h_tokens);
/// exit_status.c
char					*handle_exit_status(char *value, t_token **h_token);

#endif
