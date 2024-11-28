/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:06:34 by phautena          #+#    #+#             */
/*   Updated: 2024/11/28 15:07:57 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_files(t_token *current, int mode)
{
	t_token	*temp;
	int		res;

	temp = current;
	res = 0;
	while (temp && temp->token != CMD && temp->token != BUILTIN)
	{
		if (mode == 0)
		{
			if (temp->token == FIL && ((temp->prev && temp->prev->token == IN) || (temp->next && temp->next->token == IN)))
				res++;
			temp = temp->next;
		}
		else
		{
			if (temp->token == FIL && ((temp->prev && temp->prev->token == OUT)))
				res++;
			temp = temp->next;
		}
	}
	return (res);
}

static int	*set_infiles(t_token *current, int n_files)
{
	int		*res;
	int		i;
	t_token	*temp;

	res = malloc(sizeof(int) * n_files);
	if (!res)
		return (printf("Failed to allocate memory for infiles\n"), NULL);
	i = 0;
	temp = current;
	while (temp && temp->token != CMD && temp->token != BUILTIN)
	{
		if (temp->token == FIL && ((temp->prev && temp->prev->token == IN) || (temp->next && temp->next->token == IN)))
		{
			res[i] = open(temp->value, O_RDONLY);
			if (res[i] < 0)
				return (printf("Failed to open file: %s\n", temp->value), NULL);
			i++;
		}
		temp = temp->next;
	}
	return (res);
}

static int	*set_outfiles(t_token *current, int n_files)
{
	int		*res;
	int		i;
	t_token	*temp;

	res = malloc(sizeof(int) * n_files);
	if (!res)
		return (printf("Failed to allocate memory for outfiles\n"), NULL);
	i = 0;
	temp = current;
	while (temp && temp->token != CMD && temp->token != BUILTIN)
	{
		if (temp->token == FIL && ((temp->prev && temp->prev->token == OUT)))
		{
			res[i] = open(temp->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (res[i] < 0)
				return (printf("Failed to open file: %s\n", temp->value), NULL);
			i++;
		}
		temp = temp->next;
	}
	return (res);
}

int	set_redirs_in(t_token **h_token, t_cmd **h_cmd)
{
	t_cmd	*t_cmd;
	t_token	*t_token;

	t_cmd = *h_cmd;
	t_token = (*h_token)->next;
	while (t_cmd)
	{
		if (!t_token)
			return (0);
		t_cmd->infiles = count_files(t_token, 0);
		if (t_cmd->infiles < 1)
			;
		else
		{
			t_cmd->fd_in = set_infiles(t_token, t_cmd->infiles);
			if (!t_cmd->fd_in)
				return (1);
		}
		while (t_token->next && t_token->token != PIPE)
			t_token = t_token->next;
		if (t_cmd->next)
			t_token = t_token->next->next;
		t_cmd = t_cmd->next;
	}
	return (0);
}

int	set_redirs_out(t_token **h_token, t_cmd **h_cmd)
{
	t_cmd	*t_cmd;
	t_token	*t_token;

	t_cmd = *h_cmd;
	t_token = (*h_token)->next;
	while (t_cmd)
	{
		if (!t_token)
			return (0);
		t_cmd->outfiles = count_files(t_token, 1);
		if (t_cmd->outfiles < 1)
			;
		else
		{
			t_cmd->fd_out = set_outfiles(t_token, t_cmd->outfiles);
			if (!t_cmd->fd_out)
				return (1);
		}
		while (t_token->next && t_token->token != PIPE)
			t_token = t_token->next;
		if (t_cmd->next)
			t_token = t_token->next->next;
		t_cmd = t_cmd->next;
	}
	return (0);
}
