/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:12:35 by phautena          #+#    #+#             */
/*   Updated: 2024/12/03 13:11:35 by pbailly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_var(char **envp, t_head *head)
{
	head->h_env = NULL;
	init_env(&head->h_env, envp);
	export_var("TEST=LMAO", &head->h_env);
	// print_env(&head->h_env);
}

void	export_var(char *var, t_env **h_env)
{
	char	*name;
	char	*value;

	if (!var)
		return ;
	if (export_var_parsing(var))
		return ;
	name = get_env_name(var);
	if (!name)
		return ;
	unset(name, h_env);
	if (!ft_strchr(var, '='))
	{
		add_env_end(name, NULL, h_env);
		return ;
	}
	value = export_env_value(var);
	if (!value)
		value = NULL;
	add_env_end(name, value, h_env);
}

void	print_export(t_env **h_env)
{
	t_env	*temp;

	if (*h_env == NULL)
		return ;
	temp = *h_env;
	while (temp)
	{
		if (temp->value)
			printf("export %s=\"%s\"\n", temp->name, temp->value);
		else
			printf("export %s\n", temp->name);
		temp = temp->next;
	}
}

void	print_env(t_env **h_env)
{
	t_env	*temp;

	if (*h_env == NULL)
		return ;
	temp = *h_env;
	while (temp)
	{
		if (temp->value)
			printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

char	*get_var(char *name, t_env **h_env)
{
	int		len;
	t_env	*temp;

	if (!name || *h_env == NULL)
		return (NULL);
	len = ft_strlen(name) - 1;
	temp = *h_env;
	while (temp)
	{
		if (!ft_strcmp(name, temp->name))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
