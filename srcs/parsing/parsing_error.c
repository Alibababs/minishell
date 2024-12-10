/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:51:54 by alibabab          #+#    #+#             */
/*   Updated: 2024/12/10 20:26:44 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error_msg(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

static bool	invalid_pipe(t_data *data)
{
	t_token	*temp;

	temp = data->h_tokens;
	if (temp && (temp->token == PIPE || (temp->prev
				&& temp->prev->token == REDIR)))
		return (syntax_error_msg("|"), true);
	while (temp && temp->next)
	{
		if (temp->token == PIPE && temp->next->token != WORD
			&& temp->next->token != REDIR)
			return (syntax_error_msg("|"), true);
		temp = temp->next;
	}
	if (temp && temp->token == PIPE)
		return (syntax_error_msg("|"), true);
	return (false);
}

static bool	invalid_redir(t_data *data)
{
	t_token	*temp;

	temp = data->h_tokens;
	while (temp)
	{
		if (temp->token == REDIR)
		{
			if (temp->next && (temp->next->token == REDIR))
				return (syntax_error_msg(temp->value), true);
			if (!temp->next || (temp->next->token != WORD))
				return (syntax_error_msg("newline"), true);
		}
		temp = temp->next;
	}
	return (false);
}

bool	valid_syntax(t_data *data)
{
	if (invalid_pipe(data))
		return (false);
	if (invalid_redir(data))
		return (false);
	return (true);
}
