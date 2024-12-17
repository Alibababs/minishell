/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:00:38 by phautena          #+#    #+#             */
/*   Updated: 2024/12/17 15:01:46 by p0ulp1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_path(t_data *data)
{
	int		cmd_n;
	t_cmd	*cmd_temp;
	t_token	*token_temp;

	cmd_n = count_cmds(data);
	cmd_temp = data->h_cmds;
	token_temp = data->h_tokens;
	while (cmd_n-- > 0)
	{
		if (is_builtin(token_temp))
		{
			cmd_temp->path = ft_strdup(token_temp->value);
			if (!cmd_temp->path)
				mem_error(&data);
		}
		else
			set_path_cmd(token_temp, cmd_temp, data);
		cmd_temp = cmd_temp->next;
		if (cmd_n > 0)
		{
			while (token_temp->token != PIPE)
				token_temp = token_temp->next;
			token_temp = token_temp->next;
		}
	}
}

static void	init_cmd_nodes(t_data *data)
{
	t_token	*temp;
	int		cmd_n;

	temp = data->h_tokens;
	cmd_n = 1;
	while (temp)
	{
		if (temp->token == PIPE)
			cmd_n++;
		temp = temp->next;
	}
	while (cmd_n > 0)
	{
		add_cmd_end(data);
		cmd_n--;
	}
}

int	exec(t_data *data)
{
	init_cmd_nodes(data);
	set_path(data);
	set_argv(data);
	if (set_redirs(data))
		return (1);
	return (0);
}


