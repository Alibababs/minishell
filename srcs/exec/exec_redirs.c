/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:17:55 by phautena          #+#    #+#             */
/*   Updated: 2025/01/16 14:04:02 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_dup(t_cmd *cmd)
{
	if (cmd->infile > -1)
		dup2(cmd->infile, STDIN_FILENO);
	else
		dup2(cmd->to_read, STDIN_FILENO);
	if (cmd->outfile > -1)
		dup2(cmd->outfile, STDOUT_FILENO);
	else
		dup2(cmd->to_write, STDOUT_FILENO);
}

int	init_infiles(t_data **data)
{
	t_token	*tp;
	t_cmd	*cmd;

	tp = (*data)->h_tokens;
	cmd = (*data)->h_cmds;
	while (tp)
	{
		if (tp->token == PIPE)
			cmd = cmd->next;
		else if (tp->token == REDIR && !ft_strcmp(tp->value, "<"))
		{
			if (cmd->infile > -1)
				close(cmd->infile);
			cmd->infile = open(tp->next->value, O_RDONLY);
			if (cmd->infile == -1)
				return (perror(tp->next->value), 1);
		}
		tp = tp->next;
	}
	cmd = cmd->next;
	return (0);
}

int	init_outfiles(t_data **data)
{
	t_token	*tp;
	t_cmd	*cmd;

	tp = (*data)->h_tokens;
	cmd = (*data)->h_cmds;
	while (tp)
	{
		if (tp->token == PIPE)
			cmd = cmd->next;
		else if (tp->token == REDIR && tp->value[0] == '>')
		{
			if (cmd->outfile > -1)
				close(cmd->outfile);
			if (!ft_strcmp(tp->value, ">"))
				cmd->outfile = open(tp->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (!ft_strcmp(tp->value, ">>"))
				cmd->outfile = open(tp->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (cmd->outfile == -1)
				return (perror(tp->value), 1);
		}
		tp = tp->next;
	}
	return (0);
}
