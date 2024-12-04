/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:26:33 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/11/30 12:41:01 by p0ulp1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_data *data)
{
	t_env	*temp;

	printf("HEAD VALUE: %p\n", data->h_env);
	if (!data->h_env)
		return ;
	temp = data->h_env;
	while (temp)
	{
		if (temp->value)
			printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}
