/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:19:22 by alibabab          #+#    #+#             */
/*   Updated: 2024/12/10 01:16:01 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_data *data)
{
	t_token	*temp;

	temp = data->h_tokens;
	while (temp)
	{
		if (ft_strstr(temp->value, "$?"))
			temp->value = handle_exit_status(temp->value, data);
		else if (ft_strchr(temp->value, '$'))
			temp->value = handle_dollar(temp->value, data);
		temp = temp->next;
	}
	remove_empty_tokens(data);
	print_tokens(data->h_tokens);
}
