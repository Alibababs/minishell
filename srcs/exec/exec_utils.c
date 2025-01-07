/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:00:32 by phautena          #+#    #+#             */
/*   Updated: 2025/01/07 13:22:50 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_argv(t_token *token_temp)
{
	int	argv_n;

	argv_n = 0;
	while (token_temp && token_temp->token != REDIR
		&& token_temp->token != PIPE)
	{
		argv_n++;
		token_temp = token_temp->next;
	}
	return (argv_n);
}

static void	init_cmd_values(t_cmd *current)
{
	current->path = NULL;
	current->argv = NULL;
	current->infiles = NULL;
	current->outfiles = NULL;
	current->nb_infiles = 0;
	current->nb_outfiles = 0;
	current->to_read = STDIN_FILENO;
	current->to_write = STDOUT_FILENO;
	current->pid = -1;
	current->here_doc = false;
	current->no_cmd = false;
	current->hd_del = NULL;
	current->next = NULL;
	current->prev = NULL;
}

void	add_cmd_end(t_data *data)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		mem_error(&data);
	init_cmd_values(new_cmd);
	if (!data->h_cmds)
	{
		data->h_cmds = new_cmd;
		return ;
	}
	temp = data->h_cmds;
	while (temp->next)
		temp = temp->next;
	temp->next = new_cmd;
	new_cmd->prev = temp;
}

int	count_cmds(t_data *data)
{
	t_cmd	*temp;
	int		res;

	temp = data->h_cmds;
	res = 0;
	while (temp)
	{
		res++;
		temp = temp->next;
	}
	return (res);
}

int	is_builtin(char *value)
{
	if (!ft_strcmp(value, "echo"))
		return (1);
	else if (!ft_strcmp(value, "cd"))
		return (1);
	else if (!ft_strcmp(value, "export"))
		return (1);
	else if (!ft_strcmp(value, "unset"))
		return (1);
	else if (!ft_strcmp(value, "pwd"))
		return (1);
	else if (!ft_strcmp(value, "exit"))
		return (1);
	else if (!ft_strcmp(value, "env"))
		return (1);
	else
		return (0);
}
