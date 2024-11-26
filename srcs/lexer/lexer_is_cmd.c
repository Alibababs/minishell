/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_is_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:06:37 by phautena          #+#    #+#             */
/*   Updated: 2024/11/21 12:26:10 by phautena         ###   ########.fr       */
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
	if (str[0] == '$' && str[1] != '\0')
		return (0);
	return (1);
}

int	is_cmd(t_token *current)
{
	int	i;

	i = -1;
	while (current->value[++i])
	{
		if (!ft_isalpha(current->value[i]))
			return (1);
	}
	if (!current->prev)
		return (0);
	else if (current->prev->value[0] == '|')
		return (0);
	else if (current->prev->prev && current->prev->prev->token == IN)
		return (0);
	else
		return (1);
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
	free_array(splitted_path);
	if (!fixed)
		return (NULL);
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
