/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:52:31 by phautena          #+#    #+#             */
/*   Updated: 2024/11/08 15:15:38 by phautena         ###   ########.fr       */
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

void	free_env(t_env **h_env)
{
	t_env	*temp;

	if (*h_env == NULL)
		return ;
	temp = *h_env;
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

void	free_token(t_token **h_token)
{
	t_token	*temp;

	if (*h_token == NULL)
		return ;
	temp = *h_token;
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
