/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:22:38 by phautena          #+#    #+#             */
/*   Updated: 2024/11/11 16:09:35 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_cmd_list(t_token **h_token, t_cmd **h_cmd)
{
	t_token *temp;
	int		cmd_n;

	temp = *h_token;
	cmd_n = 0;
	while (temp)
	{
		if (temp->token == CMD || temp->token == BUILTIN)
			cmd_n++;
		temp = temp->next;
	}
	int x;
	x = 0;
	while (cmd_n-- > 0)
	{
		add_cmd_end(h_cmd);
		x++;
	}
}

void	parsing(t_token **h_token, t_env **h_env)
{
	t_cmd	*h_cmd;

	h_cmd = NULL;
	create_cmd_list(h_token, &h_cmd);
	(void)h_env;
}

