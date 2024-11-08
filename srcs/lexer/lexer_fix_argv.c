/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fix_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:37:03 by phautena          #+#    #+#             */
/*   Updated: 2024/11/08 11:46:27 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer_multiple_space(t_token **head)
{
	t_token	*temp;

	temp = *head;
	while (temp)
	{
		if ((temp->token == ARGV || temp->token == S_QUOTE
				|| temp->token == D_QUOTE) && temp->next
			&& ft_isspace(temp->next->value[0]) && temp->next->next
			&& ft_isspace(temp->next->next->value[0]))
		{
			del_next_redir(&temp);
			temp = *head;
		}
		temp = temp->next;
	}
}

static void	lexer_one_space(t_token **head)
{
	t_token	*temp;

	temp = *head;
	while (temp)
	{
		if ((temp->token == CMD || temp->token == BUILTIN) && temp->next
			&& ft_isspace(temp->next->value[0]))
		{
			del_next_redir(&temp);
			temp = *head;
		}
		else
			temp = temp->next;
	}
}

void	lexer_fix_master(t_token **head)
{
	lexer_one_space(head);
	lexer_multiple_space(head);
}
