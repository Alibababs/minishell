/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:38:51 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/19 23:01:52 by pbailly          ###   ########.fr       */
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
}						t_type;

typedef struct s_token
{
	t_type				token;
	char				*value;
	bool				was_quote;
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
	bool				no_cmd;
	t_token				*hd_del;
	struct s_cmd		*next;
	struct s_cmd		*prev;
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
void					ft_error(char *msg, t_data **data);
void					mem_error(t_data **data);
void					free_env(t_data *data);
void					free_data(t_data **data);
/// free_bis.c
void					free_array(char **array);
/// print.c
void					print_env(t_data **data);
void					print_tokens(t_token *temp);
void					print_cmds(t_cmd *temp);

/////////////ENV/////////////////
/// env_list.c
void					add_env_end(char *name, char *value, t_data **data);
/// init_env.c
void					init_env(t_data **data, char *envp[]);
char					*parse_env_name(char *var);
char					*parse_env_value(char *var);

/////////////LEXER///////////////
/// lexer.c
int						lexer(t_data *data, char *input);
/// lexer_utils.c
int						is_sep(char c);
int						is_quote(char c);
bool					quotes_closed(char *input);

/////////////EXPANDER/////////////
/// expander.c
int						expander(t_data *data);
/// expander_utils.c
int						in_s_quotes(char *str, char *ptr);
int						in_d_quotes(char *str, char *ptr);
int						remove_empty_tokens(t_data *data);
char					*get_var(char *value, t_data *data);
/// handle_dollar.c
char					*handle_dollar(char *value, t_data *h_data);
/// exit_status.c
char					*handle_exit_status(char *value, t_data *data);

//////////////PARSING///////////////
/// parsing.c
int						parsing(t_data *data);
/// parsing_error.c
bool					valid_syntax(t_data *data);
void					syntax_error_msg(char *token);

/////////////EXEC//////////////////
/// exec.c
int						exec(t_data *data);

/// exec_utils.c
void					add_cmd_end(t_data *data);
int						count_cmds(t_data *data);
int						is_builtin(char *value);
int						count_argv(t_token *token_temp);

/// exec_path.c
void					set_path_cmd(t_token *current, t_cmd *cmd,
							t_data *data);

/// exec_argv.c
int						count_argv(t_token *token_temp);
void					set_argv(t_data *data);

/// exec_redirs.c
int						set_redirs(t_data *data);

/// exec_cmds.c
int						exec_cmds(t_data *data);

/// exec_cmds_utils.c
int						exec_builtin(t_cmd *cmd, t_data *data);

//////////////////BUILTINS//////////////////
/// builtins.c
void					ft_cd(char **argv);
void					ft_echo(char *argv[]);
void					ft_pwd(void);
void					ft_export(t_cmd *cmd, t_data *data);
void					ft_unset(t_cmd *cmd, t_data *data);
void					ft_env(t_cmd *cmd, t_data *data);
void					ft_exit(char **argv);

#endif
