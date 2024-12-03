/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:01:47 by pbailly           #+#    #+#             */
/*   Updated: 2024/12/03 17:33:07 by pbailly          ###   ########.fr       */
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

# define ERROR 1
# define SUCCESS 0

extern int				g_exit_status;

typedef enum s_type
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
}						t_type;

typedef struct s_head	t_head;

typedef struct s_token
{
	t_type				token;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
	t_head				*head;
}						t_token;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
	t_head				*head;
}						t_env;

typedef struct s_cmd
{
	char				*path;
	char				**argv;
	int					*fd_in;
	int					*fd_out;
	int					infiles;
	int					outfiles;
	int					to_read;
	int					to_write;
	int					pid;
	struct s_cmd		*prev;
	struct s_cmd		*next;
	t_head				*head;
}						t_cmd;

typedef struct s_head
{
	t_token				*h_token;
	t_env				*h_env;
	t_cmd				*h_cmd;
}						t_head;

///////////GENERAL>
/// signal.c
void					ft_signals(int mode);
/// free.c
void					free_array(char **array);
void					free_token(t_token **h_token);
void					free_env(t_env **h_env);
void					error_token(t_token **h_token);
void					free_cmd(t_cmd **h_cmd);
/// free_bis.c
void					error_cmd(t_head *head);
void					cmd_cleanup(t_head *head);
void					close_fds(t_cmd *current);

//////////////PARSING>
/// parsing.c
int						parsing(t_head *head);
/// parsing_errors.c
int						syntax_error(t_head *head, char *str);
/// parsing_utils.c
int						parsing_is_redir(t_token *current);
int						is_shitty_redir(t_token *current);
int						parsing_pipes(t_token *current);
void					remove_quotes(t_token *current);

////////////////PRE_EXEC>
/// expander.c
void					expander(t_head *head);
/// pre_exec.c
int						pre_exec(t_token **h_token, t_cmd **h_cmd,
							t_head *head);
/// cmd_list.c
int						add_cmd_end(t_cmd **h_cmd);
int						count_cmds(t_cmd **h_cmd);
void					print_cmd(t_cmd **h_cmd);
/// cmd_argv.c
void					set_argv(t_token **h_token, t_cmd **h_cmd,
							t_head *head);
/// pre_exec_redirs.c
int						set_redirs_in(t_token **h_token, t_cmd **h_cmd);
int						set_redirs_out(t_token **h_token, t_cmd **h_cmd);

////////////////EXEC>
/// exec.c
int						exec(t_cmd **h_cmd, char **envp, t_env **h_env);
/// exec_utils.c
int						exec_is_builtin(char *str);
int						exec_builtin(t_cmd *current, t_env **h_env);
int						check_exec_cmds(t_cmd **h_cmd);

//////////////////BUILTINS>
/// env_list.c
void					add_env_empty(char *name, char *value, t_env **h_env);
void					add_env_end(char *name, char *value, t_env **h_env);
char					*get_env_name(char *var);
char					*get_env_value(char *var);
int						init_env(t_env **h_env, char **envp);
/// env_utils.c
void					print_env(t_env **h_env);
char					*get_var(char *name, t_env **h_env);
void					print_export(t_env **h_env);
void					export_var(char *var, t_env **h_env);
void					env_var(char **envp, t_head *head);
/// env_parsing.c
int						export_var_parsing(char *var);
char					*export_env_value(char *var);
/// unset.c
void					unset(char *name, t_env **h_env);
/// pwd.c
void					ft_pwd(void);
/// echo.c
void					ft_echo(char *argv[]);
/// cd.c
void					ft_cd(char **argv);
/// exit.c
void					ft_exit(char **argv);

///////////////LEXER>
/// lexer.c
int						lexer(char *input, t_token **h_token);
/// lexer_list.c
void					add_token_end(char *to_tokenize, t_token **h_token);
void					add_token_empty(char *to_tokenize, t_token **h_token);
void					print_token(t_token **h_token);
int						check_quotes_closed(char *input);
void					tokenize_env(int *i_ptr, char *input,
							t_token **h_token);
/// lexer_fix_redir.c
void					fix_redir_list(t_token **h_token);
void					fix_redir(t_token **start);
void					del_next_redir(t_token **current);
int						all_spaces(char *input);
/// lexer_is_token.c
int						is_in(char *str);
int						is_out(char *str);
int						is_append(char *str);
int						is_hd(char *str);
int						is_pipe(char *str);
/// lexer_is_token_bis.c
int						is_argv(t_type prev);
int						is_squote(char *str);
int						is_dquote(char *str);
int						is_builtin_bis(char *str, t_token **h_token);
char					**declare_builtin(void);
/// lexer_is_cmd.c
char					**get_path(void);
char					**fix_env(char **env);
int						is_cmd(t_token *current);
int						is_env(char *str);
int						is_file(t_type prev);
/// lexer_assign_token.c
void					tokenize(t_token **h_token);
int						is_sep(char c);
int						is_builtin(t_token *current, t_token **h_token);
// lexer_fix_argv.c
void					lexer_fix_master(t_token **h_token);

#endif
