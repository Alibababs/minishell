/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:12:28 by phautena          #+#    #+#             */
/*   Updated: 2024/11/28 15:05:35 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_nodes_until_pipe(t_token *h_current)
{
	t_token	*temp;
	int		i;

	temp = h_current;
	i = 0;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == IN || temp->token == OUT)
			return (i);
		else
		{
			i++;
			temp = temp->next;
		}
	}
	return (i);
}

static int	count_in_first_cmd(t_token *h_current)
{
	int		i;
	t_token	*temp;

	temp = h_current->next;
	i = 0;
	while (temp && temp->token != PIPE)
	{
		i++;
		temp = temp->next;
	}
	return (i + 1);
}

static char **in_first_cmd(t_token *h_current, t_head **head)
{
	char	**res;
	int		i;
	t_token	*temp;

	if (h_current->next->next)
		temp = h_current->next->next;
	i = 0;
	res = malloc(sizeof(char *) * count_in_first_cmd(h_current));
	if (!res)
		error_cmd(*head);
	while (temp && temp->token != PIPE)
	{
		res[i] = ft_strdup(temp->value);
		if (!res[i])
			error_cmd(*head);
		temp = temp->next;
		i++;
	}
	res[i] = ft_strdup(h_current->next->value);
	if (!res[i])
		error_cmd(*head);
	i++;
	res[i] = NULL;
	return (res);
}

static char	**get_argv(t_token *h_current, t_head *head)
{
	char	**res;
	int		n_argv;
	int		i;

	if (h_current->token == IN && h_current->next->next)
		return (in_first_cmd(h_current, &head));
	n_argv = count_nodes_until_pipe(h_current);
	res = malloc(sizeof(char *) * (n_argv + 1));
	if (!res)
		error_cmd(head);
	i = 0;
	while (i < n_argv)
	{
		res[i] = ft_strdup(h_current->value);
		if (!res[i])
			error_cmd(head);
		h_current = h_current->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	set_argv(t_token **h_token, t_cmd **h_cmd, t_head *head)
{
	t_token	*token_temp;
	t_cmd	*cmd_temp;

	cmd_temp = *h_cmd;
	token_temp = *h_token;
	while (cmd_temp)
	{
		cmd_temp->argv = get_argv(token_temp, head);
		while (token_temp->next && token_temp->token != PIPE)
			token_temp = token_temp->next;
		if (token_temp->next && token_temp->token == PIPE)
			token_temp = token_temp->next;
		cmd_temp = cmd_temp->next;
	}
}

