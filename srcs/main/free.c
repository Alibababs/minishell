/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:02:05 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/09 19:23:43 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_data **data, char *msg)
{
	printf("An error occured:\n");
	printf("%s\n", msg);
	(void)data;
}

void	mem_error_env(t_env **h_env)
{
	printf("A memory allocation has failed.\n");
	printf("Please provide more memory to the process.\nExiting\n");
	exit(1);
	(void)h_env;
}

void	mem_error_tokens(t_token **h_tokens)
{
	printf("A memory allocation has failed.\n");
	printf("Please provide more memory to the process.\nExiting\n");
	exit(1);
	(void)h_tokens;
}

void	mem_error(t_data **data)
{
	printf("A memory allocation has failed.\n");
	printf("Please provide more memory to the process.\nExiting\n");
	exit(1);
	(void)data;
}

void	free_env(t_data **data)
{
	t_env	*temp;
	t_env	*next;

	temp = (*data)->h_env;
	while (temp)
	{
		next = temp->next;
		if (temp->name)
			free(temp->name);
		if (temp->value)
			free(temp->value);
		if (temp)
			free(temp);
		temp = next;
	}
}

void	free_data(t_data **data)
{
	free_env(data);
	free(*data);
}
