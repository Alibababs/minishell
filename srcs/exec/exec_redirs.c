/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:09:10 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/17 15:04:22 by p0ulp1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_outfiles(t_token *token_temp, t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	cmd->outfiles = malloc(sizeof(int) * cmd->nb_outfiles);
	if (!cmd->outfiles)
		mem_error(&data);
	while (i < cmd->nb_outfiles)
	{
		if (!ft_strcmp(token_temp->value, ">") || !ft_strcmp(token_temp->value, ">>"))
		{
			cmd->outfiles[i] = open(token_temp->next->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (cmd->outfiles[i] < 0)
				return (perror(token_temp->next->value), 1);
			i++;
		}
		token_temp = token_temp->next;
	}
	return (0);
}

static int	set_infiles(t_token *token_temp, t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	cmd->infiles = malloc(sizeof(int) * cmd->nb_infiles);
	if (!cmd->infiles)
		mem_error(&data);
	while (i < cmd->nb_infiles)
	{
		if (!ft_strcmp(token_temp->value, "<"))
		{
			cmd->infiles[i] = open(token_temp->next->value, O_RDONLY);
			if (cmd->infiles[i] < 0)
				return (perror(token_temp->next->value), 1);
			i++;
		}
		token_temp = token_temp->next;
	}
	return (0);
}

static void	count_redirs(t_token *token_temp, t_cmd *cmd)
{
	int	redir_in;
	int	redir_out;

	redir_in = 0;
	redir_out = 0;
	while (token_temp && token_temp->token != PIPE)
	{
		if (token_temp->token == REDIR)
		{
			if (!ft_strcmp(token_temp->value, ">")
				|| !ft_strcmp(token_temp->value, ">>"))
				redir_out++;
			else if (!ft_strcmp(token_temp->value, "<"))
				redir_in++;
		}
		token_temp = token_temp->next;
	}
	cmd->nb_infiles = redir_in;
	cmd->nb_outfiles = redir_out;
}

static void	set_heredoc(t_token *token_temp, t_cmd *cmd)
{
	while (token_temp && token_temp->token != PIPE)
	{
		if (!ft_strcmp(token_temp->value, "<<"))
		{
			cmd->here_doc = true;
			cmd->hd_del = token_temp->next;
		}
		token_temp = token_temp->next;
	}
}

int	set_redirs(t_data *data)
{
	int		cmd_n;
	t_cmd	*cmd_temp;
	t_token	*token_temp;

	cmd_n = count_cmds(data);
	cmd_temp = data->h_cmds;
	token_temp = data->h_tokens;
	while (cmd_n-- > 0)
	{
		count_redirs(token_temp, cmd_temp);
		if (set_infiles(token_temp, cmd_temp, data))
			return (1);
		if (set_outfiles(token_temp, cmd_temp, data))
			return (2);
		set_heredoc(token_temp, cmd_temp);
		cmd_temp = cmd_temp->next;
		if (cmd_n > 0)
		{
			while (token_temp->token != PIPE)
				token_temp = token_temp->next;
			token_temp = token_temp->next;
		}
	}
	return (0);
}
