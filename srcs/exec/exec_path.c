/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:44:51 by phautena          #+#    #+#             */
/*   Updated: 2025/01/30 10:28:41 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**fix_env(char **env)
{
	char	**res;
	int		len;
	int		i;

	len = 0;
	while (env[len])
		len++;
	res = malloc((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (env[i])
	{
		res[i] = ft_strjoin(env[i], "/");
		if (!res[i])
			return (NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}

static char	**get_path(t_data **data)
{
	char	*path;
	char	**splitted_path;
	char	**fixed;

	path = get_var("PATH", data);
	if (!path)
		return (NULL);
	splitted_path = ft_split(path, ':');
	if (!splitted_path)
		return (NULL);
	fixed = fix_env(splitted_path);
	free_array(splitted_path);
	if (!fixed)
		return (NULL);
	return (fixed);
}

char	*get_cmd_path(char *binary, t_data **data)
{
	int		i;
	char	**path;
	char	*path_binary;

	i = 0;
	path = get_path(data);
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

static char	*set_path_bis(t_token *current, t_cmd *cmd, t_data **data)
{
	if (current->value[0] != '/')
	{
		cmd->path = get_cmd_path(current->value, data);
		if (!cmd->path)
		{
			cmd->path = ft_strdup(current->value);
			if (!cmd->path)
				mem_error(data);
		}
	}
	else
	{
		cmd->path = ft_strdup(current->value);
		if (!cmd->path)
			mem_error(data);
	}
	return (NULL);
}

void	set_path_cmd(t_token *current, t_cmd *cmd, t_data **data)
{
	while (current)
	{
		if (current->token == PIPE)
			current = current->next;
		else if (current->token == WORD)
		{
			set_path_bis(current, cmd, data);
			return ;
		}
		else if (current->token == REDIR && (!current->next->next
				|| current->next->next->token == PIPE))
		{
			cmd->no_cmd = true;
			cmd->path = ft_strdup("no_cmd");
			if (!cmd->path)
				mem_error(data);
			return ;
		}
		else
			current = current->next->next;
	}
}
