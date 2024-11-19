/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:22:38 by phautena          #+#    #+#             */
/*   Updated: 2024/11/19 13:38:46 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cmd_path(char *binary)
{
	int		i;
	char	**path;
	char	*path_binary;

	i = 0;
	path = get_path();
	if (!path)
		return (NULL);
	while (path[i])
	{
		path_binary = ft_strjoin(path[i], binary);
		if (!path_binary)
			return (free_array(path), NULL);
		if (!access(path_binary, F_OK))
			return (free_array(path), path_binary);
		free(path_binary);
		i++;
	}
	free_array(path);
	return (binary);
}

static void	set_cmd(t_token *token_current, t_cmd *cmd_current)
{
	if (token_current->value[0] != '/')
		cmd_current->path = get_cmd_path(token_current->value);
	else
		cmd_current->path = ft_strdup(token_current->value);
}

static void	set_path(t_token **h_token, t_cmd **h_cmd)
{
	int		cmd_n;
	t_cmd	*cmd_temp;
	t_token	*token_temp;

	cmd_n = count_cmds(h_cmd);
	cmd_temp = *h_cmd;
	token_temp = *h_token;
	while (token_temp && cmd_n > 0)
	{
		if (token_temp->token == CMD)
		{
			set_cmd(token_temp, cmd_temp);
			cmd_temp = cmd_temp->next;
			cmd_n--;
		}
		else if (token_temp->token == BUILTIN)
		{
			cmd_temp->path = ft_strdup(token_temp->value);
			cmd_temp = cmd_temp->next;
			cmd_n--;
		}
		token_temp = token_temp->next;
	}
}

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
	while (cmd_n > 0)
	{
		add_cmd_end(h_cmd);
		cmd_n--;
	}
}

void	parsing(t_token **h_token, t_cmd **h_cmd)
{
	create_cmd_list(h_token, h_cmd);
	set_path(h_token, h_cmd);
	print_cmd(h_cmd);
}

