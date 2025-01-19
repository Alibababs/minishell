/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:51:54 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/19 13:10:54 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error_msg(char *token)
{
	if (token[0] == '>' && ft_strlen(token) == 3)
		token = ">";
	else if (token[0] == '>' && ft_strlen(token) > 3)
		token = ">>";
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	g_exit_status = 2;
}

static bool	invalid_pipe(t_data **data)
{
	t_token	*temp;

	temp = (*data)->h_tokens;
	if (temp && temp->token == PIPE && temp->next && temp->next->token == PIPE)
		return (syntax_error_msg("||"), true);
	if (temp && (temp->token == PIPE || (temp->prev
				&& temp->prev->token == REDIR)))
		return (syntax_error_msg("|"), true);
	while (temp && temp->next)
	{
		if (temp->token == PIPE && temp->next->token != WORD
			&& temp->next->token != REDIR)
			return (syntax_error_msg("|"), true);
		if (temp->token == PIPE && temp->prev && temp->prev->token == REDIR)
			return (syntax_error_msg("|"), true);
		temp = temp->next;
	}
	if (temp && temp->token == PIPE)
		return (syntax_error_msg("|"), true);
	return (false);
}

static bool	invalid_dir(t_data **data)
{
	t_token	*temp;
	int		fd;

	temp = (*data)->h_tokens;
	while (temp)
	{
		if (!temp->prev || temp->prev->token == PIPE)
		{
			fd = open(temp->value, __O_DIRECTORY);
			if (fd > -1 && ft_strchr(temp->value, '/'))
			{
				close(fd);
				ft_putstr_fd("minishell : ", 2);
				ft_putstr_fd(temp->value, 2);
				ft_putstr_fd(": Is a directory\n", 2);
				return (true);
			}
		}
		temp = temp->next;
	}
	return (false);
}

static bool	invalid_redir(t_data **data)
{
	t_token	*temp;

	temp = (*data)->h_tokens;
	while (temp)
	{
		if (temp->token == REDIR)
		{
			if (temp->prev && (temp->prev->token == REDIR))
				return (syntax_error_msg(temp->value), true);
			if (!temp->next)
				return (syntax_error_msg("newline"), true);
		}
		temp = temp->next;
	}
	return (false);
}

int	parsing(t_data **data)
{
	if (invalid_pipe(data))
	{
		g_exit_status = 2;
		return (1);
	}
	if (invalid_redir(data))
	{
		g_exit_status = 2;
		return (1);
	}
	if (invalid_dir(data) == true)
	{
		g_exit_status = 126;
		return (1);
	}
	return (0);
}
