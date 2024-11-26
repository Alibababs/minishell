/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:23:14 by phautena          #+#    #+#             */
/*   Updated: 2024/11/21 13:49:58 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	single_char_redir_errors(t_head *head)
{
	t_token	*temp;

	temp = head->h_token;
	if (temp->token == NDEF && ft_strlen(temp->value) == 1)
		return (syntax_error(head, temp->value));
	while (temp)
	{
		if (parsing_is_redir(temp) && !temp->next)
			return (syntax_error(head, "newline"));
		if (is_shitty_redir(temp))
			return (syntax_error(head, temp->value));
		temp = temp->next;
	}
	return (0);
}

int	parsing(t_head *head)
{
	if (single_char_redir_errors(head))
		return (1);
	return (0);
}
