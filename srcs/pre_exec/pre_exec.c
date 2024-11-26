/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:22:38 by phautena          #+#    #+#             */
/*   Updated: 2024/11/26 15:42:31 by phautena         ###   ########.fr       */
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
	return (ft_strdup(binary));
}

static void	set_cmd(t_token *token_current, t_cmd *cmd_current, t_head *head)
{
	if (token_current->value[0] != '/')
	{
		cmd_current->path = get_cmd_path(token_current->value);
		if (!cmd_current->path)
			error_cmd(head);
	}
	else
	{
		cmd_current->path = ft_strdup(token_current->value);
		if (!cmd_current->path)
			error_cmd(head);
	}
}

static void	set_path(t_token **h_token, t_cmd **h_cmd, t_head *head)
{
	int		cmd_n;
	t_cmd	*cmd_temp;
	t_token	*token_temp;

	cmd_n = count_cmds(h_cmd);
	cmd_temp = *h_cmd;
	token_temp = *h_token;
	while (token_temp && cmd_n > 0)
	{
		if (token_temp->token == CMD || token_temp->token == ENV)
		{
			set_cmd(token_temp, cmd_temp, head);
			cmd_temp = cmd_temp->next;
			cmd_n--;
		}
		else if (token_temp->token == BUILTIN)
		{
			cmd_temp->path = ft_strdup(token_temp->value);
			if (!cmd_temp->path)
				error_cmd(head);
			cmd_temp = cmd_temp->next;
			cmd_n--;
		}
		token_temp = token_temp->next;
	}
}

static int	create_cmd_list(t_token **h_token, t_cmd **h_cmd)
{
	t_token *temp;
	int		cmd_n;

	temp = *h_token;
	cmd_n = 0;
	while (temp)
	{
		if (temp->token == CMD || temp->token == BUILTIN
			|| (temp->token == ENV && (!temp->prev || temp->prev->token == PIPE)))
			cmd_n++;
		temp = temp->next;
	}
	while (cmd_n > 0)
	{
		if (add_cmd_end(h_cmd) != 0)
			return (1);
		cmd_n--;
	}
	return (0);
}

int	pre_exec(t_token **h_token, t_cmd **h_cmd, t_head *head)
{
	if (create_cmd_list(h_token, h_cmd) != 0)
		error_cmd(head);
	set_path(h_token, h_cmd, head);
	set_argv(h_token, h_cmd, head);
	if (set_redirs_in(h_token, h_cmd) || set_redirs_out(h_token, h_cmd))
		return (1);
	print_cmd(h_cmd);
	return (0);
}

