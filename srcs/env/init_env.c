/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:06:24 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/05 10:58:51 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_data **data, char *envp[])
{
	int		i;
	char	*name;
	char	*value;

	(*data)->envp = envp;
	if (!(*data)->envp)
		return (ft_error(data, "Please provide ENV variables\n"));
	i = 0;
	while (envp[i])
	{
		name = parse_env_name(envp[i]);
		if (!name)
			return (mem_error(data));
		value = parse_env_value(envp[i]);
		if (!value)
			return (free(name), mem_error(data));
		add_env_end(name, value, data);
		i++;
	}
}

char	*parse_env_name(char *var)
{
	int		i;
	char	*name;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	name = ft_substr(var, 0, i);
	if (!name)
		return (NULL);
	return (name);
}

char	*parse_env_value(char *var)
{
	int		i;
	char	*value;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	i++;
	value = ft_substr(var, i, ft_strlen(var));
	if (!value)
		return (NULL);
	return (value);
}
