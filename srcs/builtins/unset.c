/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:01:19 by alibabab          #+#    #+#             */
/*   Updated: 2024/12/20 22:14:28 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_destroy(t_env *temp)
{
	if (temp->prev && temp->next)
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	else if (temp->next)
		temp->next->prev = NULL;
	else if (temp->prev)
		temp->prev->next = NULL;
	if (temp->name)
		free(temp->name);
	if (temp->value)
		free(temp->value);
	free(temp);
}

void	ft_unset(char **argv, t_data *data)
{
	t_env	*temp;
	char	*name;

	if (!argv[1])
		return ;
	name = argv[1];
	temp = data->h_env;
	while (temp)
	{
		if (!ft_strcmp(name, temp->name))
		{
			unset_destroy(temp);
			return ;
		}
		temp = temp->next;
	}
}
