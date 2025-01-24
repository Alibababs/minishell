/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:00:32 by phautena          #+#    #+#             */
/*   Updated: 2025/01/24 11:43:40 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_cmd_values(t_cmd *current)
{
	current->path = NULL;
	current->argv = NULL;
	current->to_read = -1;
	current->to_write = -1;
	current->infile = -2;
	current->outfile = -2;
	current->pid = -1;
	current->ex_stat = -1;
	current->here_doc = false;
	current->no_cmd = false;
	current->hd_del = NULL;
	current->next = NULL;
	current->prev = NULL;
}

void	add_cmd_end(t_data **data)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		mem_error(data);
	init_cmd_values(new_cmd);
	if (!(*data)->h_cmds)
	{
		(*data)->h_cmds = new_cmd;
		return ;
	}
	temp = (*data)->h_cmds;
	while (temp->next)
		temp = temp->next;
	temp->next = new_cmd;
	new_cmd->prev = temp;
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

void	init_cmd_nodes(t_data **data)
{
	t_token	*temp;
	int		cmd_n;

	temp = (*data)->h_tokens;
	cmd_n = 1;
	while (temp)
	{
		if (temp->token == PIPE)
			cmd_n++;
		temp = temp->next;
	}
	while (cmd_n > 0)
	{
		add_cmd_end(data);
		cmd_n--;
	}
}

int	init_pipes(t_data **data)
{
	t_cmd	*cmd;
	int		pipefd[2];

	cmd = (*data)->h_cmds;
	if (cmd->to_read == -1)
		cmd->to_read = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next && cmd->to_write == -1 && cmd->next->to_read == -1)
		{
			if (pipe(pipefd) == -1)
				return (1);
			cmd->to_write = pipefd[1];
			cmd->next->to_read = pipefd[0];
		}
		if (!cmd->next && cmd->to_write == -1)
			cmd->to_write = STDOUT_FILENO;
		cmd = cmd->next;
	}
	return (0);
}
