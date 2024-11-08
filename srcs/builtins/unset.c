/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:27:27 by phautena          #+#    #+#             */
/*   Updated: 2024/11/07 14:27:35 by phautena         ###   ########.fr       */
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
	temp = NULL;
}

void	unset(char *name, t_env **head)
{
	t_env	*temp;

	temp = *head;
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(name) + 1))
		{
			unset_destroy(temp);
			return ;
		}
		temp = temp->next;
	}
}
