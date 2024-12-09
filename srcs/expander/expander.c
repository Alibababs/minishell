/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:19:22 by alibabab          #+#    #+#             */
/*   Updated: 2024/12/09 16:46:41 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_token **h_tokens)
{
	t_token	*temp;

	temp = *h_tokens;
	while (temp)
	{
		if (ft_strstr(temp->value, "$?"))
			temp->value = handle_exit_status(temp->value, h_tokens);
		temp = temp->next;
	}
	print_tokens(*h_tokens);
}
