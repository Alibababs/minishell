/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:12:28 by phautena          #+#    #+#             */
/*   Updated: 2024/11/19 16:55:15 by phautena         ###   ########.fr       */
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
		i++;
		temp = temp->next;
	}
	return (i);
}

static char	**get_argv(t_token *h_current)
{
	char	**res;
	int		n_argv;
	int		i;

	n_argv = count_nodes_until_pipe(h_current);
	res = malloc(sizeof(char *) * n_argv + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < n_argv)
	{
		res[i] = ft_strdup(h_current->value);
		h_current = h_current->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	set_argv(t_token **h_token, t_cmd **h_cmd)
{
	t_token	*token_temp;
	t_cmd	*cmd_temp;

	cmd_temp = *h_cmd;
	token_temp = *h_token;
	while (cmd_temp)
	{
		cmd_temp->argv = get_argv(token_temp);
		while (token_temp->next && token_temp->token != PIPE)
			token_temp = token_temp->next;
		if (token_temp->next && token_temp->token == PIPE)
			token_temp = token_temp->next;
		cmd_temp = cmd_temp->next;
	}
}

