/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:26:02 by phautena          #+#    #+#             */
/*   Updated: 2024/10/04 15:25:29 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(t_env **head, char **envp)
{
	int		i;
	char	*name;
	char	*value;

	if (!envp)
		return (1);
	i = 0;
	while (envp[i])
	{
		name = get_env_name(envp[i]);
		if (!name)
			return (2);
		value = get_env_value(envp[i]);
		if (!value)
			return (free(name), 3);
		add_env_end(name, value, head);
		i++;
	}
	return (0);
}

char	*get_env_name(char *var)
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

char	*get_env_value(char *var)
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

void	add_env_empty(char *name, char *value, t_env **head)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return ;
	new_env->name = name;
	new_env->value = value;
	new_env->prev = NULL;
	new_env->next = NULL;
	*head = new_env;
}

void	add_env_end(char *name, char *value, t_env **head)
{
	t_env	*new_env;
	t_env	*temp;

	if (*head == NULL)
		add_env_empty(name, value, head);
	else
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			return ;
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_env;
		new_env->next = NULL;
		new_env->prev = temp;
		new_env->name = name;
		new_env->value = value;
	}
}
