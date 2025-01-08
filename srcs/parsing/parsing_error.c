/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:51:54 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/08 13:44:56 by phautena         ###   ########.fr       */
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

static	bool invalid_dir(t_data *data)
{
	t_token	*temp;
	int		i;

	temp = data->h_tokens;
	i = 0;
	while (temp)
	{
		if (!temp->prev || temp->prev->token == PIPE)
		{
			while (temp->value[i])
			{
				if (temp->value[i] != '.' && temp->value[i] != '/')
					return (false);
				i++;
			}
			printf("%s: Is a directory\n", temp->value);
			return (true);
		}
		temp = temp->next;
	}
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
	if (invalid_dir(data) == true)
		return (false);
	return (true);
}
