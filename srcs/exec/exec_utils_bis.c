/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:59:10 by phautena          #+#    #+#             */
/*   Updated: 2025/01/16 11:16:35 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_argv(t_token *token_temp)
{
	int	argv_n;

	argv_n = 0;
	while (token_temp && token_temp->token != PIPE)
	{
		if (token_temp->token == REDIR)
			token_temp = token_temp->next->next;
		else if (token_temp)
		{
			argv_n++;
			token_temp = token_temp->next;
		}
	}
	return (argv_n);
}

int	count_cmds(t_data **data)
{
	t_cmd	*temp;
	int		res;

	temp = (*data)->h_cmds;
	res = 0;
	while (temp)
	{
		res++;
		temp = temp->next;
	}
	return (res);
}
