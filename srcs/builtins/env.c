/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:15:17 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/24 11:23:56 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*get_shlvl(t_data **data)
{
	t_env	*temp;

	temp = (*data)->h_env;
	while (temp)
	{
		if (!ft_strcmp(temp->name, "SHLVL"))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	shlvl(t_data **data)
{
	t_env	*shlvl;
	int		old_value;

	shlvl = get_shlvl(data);
	if (!shlvl)
		return ;
	old_value = ft_atoi(shlvl->value);
	old_value++;
	free(shlvl->value);
	shlvl->value = ft_itoa(old_value);
	if (!shlvl->value)
		mem_error(data);
}

void	ft_env(t_data **data)
{
	t_env	*temp;

	temp = (*data)->h_env;
	while (temp)
	{
		if (temp->value && *temp->value)
			printf("%s=\"%s\"\n", temp->name, temp->value);
		else if (temp->empty_value == true)
			printf("%s=\n", temp->name);
		temp = temp->next;
	}
}
