/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:06:24 by p0ulp1            #+#    #+#             */
/*   Updated: 2025/01/22 12:43:29 by alibabab         ###   ########.fr       */
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
	{
		ft_putstr_fd("Please provide ENV variables\n", 2);
		free_data(data);
		exit(1);
	}
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
		free(name);
		free(value);
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

static void	update_env_value(char *name, char *value, t_data **data)
{
	t_env	*temp;

	temp = (*data)->h_env;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
}

void	add_env_end(char *name, char *value, t_data **data)
{
	t_env	*new_env;
	t_env	*temp;

	update_env_value(name, value, data);
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		mem_error(data);
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	if (!new_env->name || !new_env->value)
		mem_error(data);
	new_env->data = *data;
	new_env->prev = NULL;
	new_env->next = NULL;
	new_env->empty_value = NULL;
	if (!(*data)->h_env)
		(*data)->h_env = new_env;
	else
	{
		temp = (*data)->h_env;
		while (temp->next)
			temp = temp->next;
		temp->next = new_env;
		new_env->prev = temp;
	}
}
