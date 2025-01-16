/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:15:17 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/16 08:57:05 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
