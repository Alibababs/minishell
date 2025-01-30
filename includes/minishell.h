/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:38:51 by p0ulp1            #+#    #+#             */
/*   Updated: 2025/01/30 10:32:13 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
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
	bool				empty_value;
	t_data				*data;
}						t_env;

typedef struct s_cmd
{
	char				*path;
	char				**argv;
	int					to_read;
	int					to_write;
	int					infile;
	int					outfile;
	int					pid;
	int					ex_stat;
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

typedef struct s_export_info
{
	char				*name;
	char				*value;
	bool				empty_value;
	t_data				**data;
}						t_export_info;

////////////////MAIN/////////////
/// signals.c
void					ft_signals(int mode);

/// error_msg.c
void					ft_put_error(char *str, char *str2);
void					mem_error(t_data **data);
void					ft_heredoc_error(char *str);
void					fork_error(t_data **data);

/// free.c
void					free_env(t_data **data);
void					free_data(t_data **data);
void					free_tokens(t_data **data);
void					free_array(char **array);
void					free_cmds(t_data **data);
/// print.c
void					print_env(t_data **data);
void					print_tokens(t_token *temp);
void					print_cmds(t_cmd *temp);

/////////////ENV/////////////////
/// init_env.c
void					init_env(t_data **data, char *envp[]);
char					*parse_env_name(char *var);
char					*parse_env_value(char *var);
void					add_env_end(char *name, char *value, t_data **data);

/////////////LEXER///////////////
/// lexer.c
int						lexer(t_data **data, char *input);
/// lexer_utils.c
int						is_sep(char c);
int						is_quote(char c);
bool					quotes_closed(char *input);
void					add_token_quote(t_data **data, t_type type, char *str,
							int len);

/////////////EXPANDER/////////////
/// expander.c
int						expander(t_data **data);
/// expander_utils.c
int						in_s_quotes(char *str, char *ptr);
int						in_d_quotes(char *str, char *ptr);
int						remove_empty_tokens(t_data **data);
char					*get_var(char *value, t_data **data);
/// handle_dollar.c
char					*handle_dollar(char *value, t_data **h_data);
/// exit_status.c
char					*handle_exit_status(char *value, t_data **data);

//////////////PARSING///////////////
/// parsing.c
int						parsing(t_data **data);
void					syntax_error_msg(char *token);

/////////////EXEC//////////////////
/// exec.c
int						exec(t_data **data);
void					close_pipes(t_data **data);
void					wait_for_all(t_data **data);
void					check_cmd(t_cmd *cmd, t_data **data);

/// exec_utils.c
void					add_cmd_end(t_data **data);
int						is_builtin(char *value);
void					init_cmd_nodes(t_data **data);
int						init_pipes(t_data **data);

/// exec_utils_bis.c
int						count_argv(t_token *token_temp);
int						count_cmds(t_data **data);

/// exec_temp_redirs.c
void					init_redirections(t_data **data);

/// exec_temp_files.c
int						set_outfile(t_cmd *cmd, t_token *token, int mode);
int						set_infile(t_cmd *cmd, t_token *token);
int						set_here_doc(t_cmd *cmd, t_token *token, t_data **data);
void					make_dup(t_cmd *cmd);
int						check_redirs(t_cmd *cmd, t_data **data);

/// exec_hd.c
int						init_here_doc(t_token *tp, t_data **data);

/// exec_path.c
char					*get_cmd_path(char *binary, t_data **data);
void					set_path_cmd(t_token *current, t_cmd *cmd,
							t_data **data);

/// exec_argv.c
void					set_path(t_data **data);
void					set_argv(t_data **data);

/// exec_bis.c
void					start_exec(t_data **data);
void					child_process(t_cmd *cmd, t_data **data);
int						single_builtin(t_cmd *cmd, t_data **data);

//////////////////BUILTINS//////////////////
/// builtins.c
int						ft_cd(char **argv, t_data **data);
void					ft_echo(char *argv[]);
void					ft_pwd(void);
void					ft_unset(char **argv, t_data **data);
int						ft_exit(char **argv, t_data **data, int save, int save2);
int						ft_export(char **argv, t_data **data);

/// builtin_utils.c
char					*ft_getenv(char *name, t_data **data);
void					ft_set_env(t_data **data, char *name, char *value,
							bool empty_value);
void					launch_builtin(t_cmd *cmd, t_data **data);
int						exec_builtin(t_cmd *cmd, t_data **data, int save, int save2);

/// env.c
void					ft_env(t_data **data);
void					shlvl(t_data **data);

#endif
