/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:02:05 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/10 16:18:28 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *msg, t_data **data)
{
	ft_putstr_fd(msg, 2);
	free_data(data);
	exit(1);
}

void	mem_error(t_data **data)
{
	perror("Memory allocation failed");
	free_data(data);
	exit(1);
}

void	free_env(t_data *data)
{
	t_env	*temp;
	t_env	*next;

	temp = data->h_env;
	while (temp)
	{
		next = temp->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		temp = next;
	}
	data->h_env = NULL;
}

void	free_tokens(t_data *data)
{
	t_token	*temp;
	t_token	*next;

	if (!data || !data->h_tokens)
		return ;
	temp = data->h_tokens;
	while (temp)
	{
		next = temp->next;
		if (temp->value)
			free(temp->value);
		free(temp);
		temp = next;
	}
	data->h_tokens = NULL;
}

void	free_data(t_data **data)
{
	if (!data || !*data)
		return ;
	if ((*data)->h_tokens)
		free_tokens(*data);
	if ((*data)->h_env)
		free_env(*data);
	free(*data);
	*data = NULL;
}
