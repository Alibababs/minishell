/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:52:31 by phautena          #+#    #+#             */
/*   Updated: 2024/10/04 13:21:07 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_env(t_env **head)
{
	t_env	*temp;

	if (*head == NULL)
		return ;
	temp = *head;
	while (temp->next)
	{
		if (temp->name)
			free(temp->name);
		if (temp->value)
			free(temp->value);
		temp = temp->next;
		free(temp->prev);
	}
	if (temp->name)
		free(temp->name);
	if (temp->value)
		free(temp->value);
	free(temp);
}

void	free_token(t_token **head)
{
	t_token	*temp;

	if (*head == NULL)
		return ;
	temp = *head;
	while (temp->next)
	{
		if (temp->value)
			free(temp->value);
		temp = temp->next;
		free(temp->prev);
	}
	if (temp->value)
		free(temp->value);
	free(temp);
}
