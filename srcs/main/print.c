/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:26:33 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/10 11:39:01 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_data **data)
{
	t_env	*temp;

	if (!(*data)->h_env)
		return ;
	temp = (*data)->h_env;
	while (temp)
	{
		if (temp->value)
			printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

void	print_tokens(t_token *data)
{
	while (data)
	{
		printf("Value: [%s], Token: [%d]\n", data->value, data->token);
		data = data->next;
	}
}
