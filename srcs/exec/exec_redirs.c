/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 22:42:59 by ubuntu            #+#    #+#             */
/*   Updated: 2025/01/30 10:31:59 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_files(t_cmd *cmd, t_token *token, t_data **data)
{
	if (!ft_strcmp(token->value, "<"))
	{
		if (set_infile(cmd, token->next))
			return (1);
	}
	else if (!ft_strcmp(token->value, "<<"))
	{
		if (set_here_doc(cmd, token, data))
			return (1);
	}
	else if (!ft_strcmp(token->value, ">"))
	{
		if (set_outfile(cmd, token->next, 1))
			return (1);
	}
	else
	{
		if (set_outfile(cmd, token->next, 0))
			return (1);
	}
	return (0);
}

static t_token	*next_token(t_token *token)
{
	while (token->token != REDIR)
		token = token->next;
	return (token);
}

static t_token	*next_pipe(t_token *token, t_cmd *cmd)
{
	if (!cmd->next)
		return (token);
	while (token->token != PIPE)
		token = token->next;
	token = token->next;
	return (token);
}

static int	count_redirections(t_token *token)
{
	t_token *temp;
	int		count;

	temp = token;
	count = 0;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == REDIR)
			count++;
		temp = temp->next;
	}
	return (count);
}

void	init_redirections(t_data **data)
{
	t_cmd	*cmd;
	t_token	*token;
	int		count;

	cmd = (*data)->h_cmds;
	token = (*data)->h_tokens;
	while (cmd)
	{
		count = count_redirections(token);
		while (count-- > 0)
		{
			token = next_token(token);
			if (set_files(cmd, token, data))
			{
				cmd->no_cmd = true;
				g_exit_status = 1;
				break ;
			}
			token = token->next;
		}
		token = next_pipe(token, cmd);
		cmd = cmd->next;
	}
}
