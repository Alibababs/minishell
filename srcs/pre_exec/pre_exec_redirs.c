/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:06:34 by phautena          #+#    #+#             */
/*   Updated: 2024/11/26 15:15:17 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_files(t_token *current)
{
	t_token	*temp;
	int		res;

	temp = current;
	res = 0;
	while (temp && temp->token != CMD && temp->token != BUILTIN)
	{
		if (temp->token == FIL)
			res++;
		temp = temp->next;
	}
	return (res);
}

static int	*set_infiles(t_token *current, t_head *head, int n_files)
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
		if (temp->token == FIL)
		{
			res[i] = open(temp->value, O_RDONLY);
			if (res[i] < 0)
				return (file_error(head, temp->value), NULL);
			i++;
		}
		temp = temp->next;
	}
	return (res);
}

int	set_redirs_in(t_token **h_token, t_cmd **h_cmd, t_head *head)
{
	int		n_files;
	t_cmd	*t_cmd;
	t_token	*t_token;

	t_cmd = *h_cmd;
	t_token = (*h_token)->next;
	while (t_cmd)
	{
		n_files = count_files(t_token);
		t_cmd->in = set_infiles(t_token, head, n_files);
		if (!t_cmd->in)
			return (1);
		while (t_token->next && t_token->token != PIPE)
			t_token = t_token->next;
		if (t_token->next && t_token->token == PIPE)
			t_token = t_token->next->next;
		t_cmd = t_cmd->next;
	}
	return (0);
}
