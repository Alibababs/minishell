/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fix_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:37:03 by phautena          #+#    #+#             */
/*   Updated: 2024/11/19 13:25:32 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer_beginning_space(t_token **h_token)
{
	t_token	*temp;

	temp = *h_token;
	while (temp && ft_isspace(temp->value[0]))
	{
		*h_token = temp->next;
		if (temp->next)
		{
			temp->next->prev = NULL;
			if (temp->value)
				free(temp->value);
			free(temp);
		}
		temp = temp->next;
	}
}

// static void	lexer_multiple_space(t_token **h_token)
// {
// 	t_token	*temp;

// 	temp = *h_token;
// 	while (temp)
// 	{
// 		if ((temp->token == ARGV || temp->token == S_QUOTE
// 				|| temp->token == D_QUOTE) && temp->next
// 			&& ft_isspace(temp->next->value[0]) && temp->next->next
// 			&& ft_isspace(temp->next->next->value[0]))
// 		{
// 			del_next_redir(&temp);
// 			temp = *h_token;
// 		}
// 		temp = temp->next;
// 	}
// }

// static void	lexer_one_space(t_token **h_token)
// {
// 	t_token	*temp;

// 	temp = *h_token;
// 	while (temp)
// 	{
// 		if ((temp->token == CMD || temp->token == BUILTIN) && temp->next
// 			&& ft_isspace(temp->next->value[0]))
// 		{
// 			del_next_redir(&temp);
// 			temp = *h_token;
// 		}
// 		else
// 			temp = temp->next;
// 	}
// }

void	lexer_fix_master(t_token **h_token)
{
	t_token	*temp;

	lexer_beginning_space(h_token);
	temp = *h_token;
	while (temp && temp->next)
	{
		if (temp->next->value[0] == ' ')
			del_next_redir(&temp);
		temp = temp->next;
	}
}
