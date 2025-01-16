/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:56:00 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/16 12:58:46 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_getenv(char *name, t_data **data)
{
	t_env	*temp;

	if (!name || !data)
		return (NULL);
	temp = (*data)->h_env;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	ft_set_env(t_data **data, char *name, char *value, bool empty_value)
{
	t_env	*temp;

	temp = (*data)->h_env;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			if (!temp->value)
				mem_error(data);
			temp->empty_value = empty_value;
			return ;
		}
		temp = temp->next;
	}
	add_env_end(name, value, data);
	ft_set_env(data, name, value, empty_value);
}
