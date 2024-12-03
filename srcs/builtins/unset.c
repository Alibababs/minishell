/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:27:27 by phautena          #+#    #+#             */
/*   Updated: 2024/12/03 13:13:05 by pbailly          ###   ########.fr       */
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

void	unset(char *name, t_env **h_env)
{
	t_env	*temp;

	temp = *h_env;
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
