/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:09:42 by ubuntu            #+#    #+#             */
/*   Updated: 2025/01/30 10:32:20 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_outfile(t_cmd *cmd, t_token *token, int mode)
{
	if (cmd->outfile > -1)
		close(cmd->outfile);
	if (mode == 1)
		cmd->outfile = open(token->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		cmd->outfile = open(token->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->outfile == -1)
	{
		perror(token->value);
		return (1);
	}
	return (0);
}

int	set_infile(t_cmd *cmd, t_token *token)
{
	if (cmd->infile > -1)
		close(cmd->infile);
	cmd->infile = open(token->value, O_RDONLY);
	if (cmd->infile == -1)
	{
		perror(token->value);
		return (1);
	}
	return (0);
}

int	set_here_doc(t_cmd *cmd, t_token *token, t_data **data)
{
	if (cmd->infile > -1)
		close(cmd->infile);
	cmd->infile = init_here_doc(token, data);
	if (cmd->infile == -1)
	{
		perror(token->next->value);
		return (1);
	}
	return (0);
}

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

int	check_redirs(t_cmd *cmd, t_data **data)
{
	if (cmd->infile == -1)
		return (1);
	if (cmd->outfile == -1)
		return (1);
	return (0);
	(void)data;
}
