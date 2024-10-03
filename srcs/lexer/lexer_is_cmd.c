/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_is_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:06:37 by phautena          #+#    #+#             */
/*   Updated: 2024/10/03 15:25:59 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_file(t_type prev)
{
	if (prev == IN || prev == OUT || prev == APPEND || prev == HEREDOC)
		return (0);
	return (1);
}

int	is_env(char *str)
{
	if (str[0] == '$')
		return (0);
	return (1);
}

int	is_cmd(char *str)
{
	int		i;
	char	**path;
	char	*path_binary;

	i = 0;
	path = get_path();
	if (!path)
		return (1);
	while (path[i])
	{
		path_binary = ft_strjoin(path[i], str);
		if (!path_binary)
			return (free_array(path), 2);
		if (!access(path_binary, F_OK))
			return (free_array(path), 0);
		free(path_binary);
		i++;
	}
	free_array(path);
	return (3);
}

char	**get_path(void)
{
	char	*path;
	char	**splitted_path;
	char	**fixed;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	splitted_path = ft_split(path, ':');
	if (!splitted_path)
		return (NULL);
	fixed = fix_env(splitted_path);
	if (!fixed)
		return (free_array(splitted_path), NULL);
	return (fixed);
}

char	**fix_env(char **env)
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
