/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:09:53 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/14 13:24:01 by p0ulp1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	get_argv(t_token *token_temp, t_cmd *cmd, t_data *data)
// {
// 	int		argv_n;
// 	int		i;
// 	char	*res;

// 	argv_n = count_argv(token_temp);
// 	i = 0;
// 	res = malloc(sizeof(char *) * (argv_n + 1));
// 	if (!res)
// 		mem_error(data);
// 	while (argv_n > 0)
// 	{
// 		res[i] = ft_strdup(token_temp->value);
// 		if (!res[i])
// 			mem_error(data);
// 		token_temp = token_temp->next;
// 		argv_n--;
// 		i++;
// 	}
// 	res[i] = NULL;
// 	cmd->argv = res;
// }

// void	set_argv(t_data *data)
// {
// 	int		cmd_n;
// 	t_cmd	*cmd_temp;
// 	t_token	*token_temp;

// 	cmd_n = count_cmds(data);
// 	cmd_temp = data->h_cmds;
// 	token_temp = data->h_tokens;
// 	while (cmd_n-- > 0)
// 	{
// 		if (token_temp->token == REDIR)
// 			get_argv_redir();
// 		else
// 			get_argv(token_temp, cmd_temp, data);
// 		cmd_temp = cmd_temp->next;
// 		if (cmd_n > 0)
// 		{
// 			while (token_temp->token != PIPE)
// 				token_temp = token_temp->next;
// 			token_temp = token_temp->next;
// 		}
// 	}
// }
