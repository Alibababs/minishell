/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_assign_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:39:50 by phautena          #+#    #+#             */
/*   Updated: 2024/11/20 11:24:25 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_token_bis(t_token **current)
{
	t_token	*temp;

	temp = *current;
	if (!is_env(temp->value))
		temp->token = ENV;
	else if (!is_cmd(temp))
		temp->token = CMD;
	else if (temp->prev)
	{
		if (!is_argv(temp->prev->token))
			temp->token = ARGV;
		else if (!is_file(temp->prev->token))
			temp->token = FIL;
		else
			temp->token = NDEF;
	}
	else
		temp->token = NDEF;
}

static void	assign_token(t_token **current, t_token **h_token)
{
	t_token	*temp;

	temp = *current;
	if (!temp->value)
		return ;
	if (!is_builtin(temp, h_token))
		temp->token = BUILTIN;
	else if (!is_in(temp->value))
		temp->token = IN;
	else if (!is_out(temp->value))
		temp->token = OUT;
	else if (!is_append(temp->value))
		temp->token = APPEND;
	else if (!is_hd(temp->value))
		temp->token = HEREDOC;
	else if (!is_pipe(temp->value))
		temp->token = PIPE;
	else if (!is_squote(temp->value))
		temp->token = S_QUOTE;
	else if (!is_dquote(temp->value))
		temp->token = D_QUOTE;
	else
		assign_token_bis(&temp);
}

void	tokenize(t_token **h_token)
{
	t_token	*temp;

	temp = *h_token;
	while (temp)
	{
		assign_token(&temp, h_token);
		temp = temp->next;
	}
}

int	is_sep(char c)
{
	if (c == '|' || c == ' ' || c == '<' || c == '>')
		return (1);
	else if (c == 34 || c == 39)
		return (1);
	else if (c == '$')
		return (1);
	return (0);
}

int	is_builtin(t_token *current, t_token **h_token)
{
	if (current->prev)
	{
		if (is_builtin_bis(current->value, h_token) && (current->prev->token == IN || current->prev->token == HEREDOC
			|| current->prev->token == OUT))
			return (1);
		if (is_builtin_bis(current->value, h_token) && (current->prev->token != BUILTIN || current->prev->token != CMD))
			return (0);
	}
	else if (is_builtin_bis(current->value, h_token))
		return (0);
	return (1);
}
