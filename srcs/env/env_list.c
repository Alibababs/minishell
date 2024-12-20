/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:08:40 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/20 17:39:00 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_env_empty(char *name, char *value, t_data **data)
{
	t_env	*new_env;

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
	(*data)->h_env = new_env;
}

void	add_env_end(char *name, char *value, t_data **data)
{
	t_env	*new_env;
	t_env	*temp;

	if (!(*data)->h_env)
		add_env_empty(name, value, data);
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		mem_error(data);
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	if (!new_env->name || !new_env->value)
		mem_error(data);
	temp = (*data)->h_env;
	while (temp->next)
		temp = temp->next;
	new_env->data = *data;
	new_env->prev = temp;
	new_env->next = NULL;
	temp->next = new_env;
}
