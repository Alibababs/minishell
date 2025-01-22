/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:44:40 by phautena          #+#    #+#             */
/*   Updated: 2025/01/22 12:03:03 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token(t_data **data, t_type type, char *str, int len)
{
	t_token	*new_token;
	t_token	*temp;

	if (len <= 0)
		return ;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		mem_error(data);
	new_token->value = ft_substr(str, 0, len);
	if (!new_token->value)
		mem_error(data);
	new_token->token = type;
	new_token->was_quote = false;
	new_token->next = NULL;
	new_token->prev = NULL;
	if (!(*data)->h_tokens)
	{
		(*data)->h_tokens = new_token;
		return ;
	}
	temp = (*data)->h_tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
	new_token->prev = temp;
}

static int	tokenize_quote(t_data **data, int *ip, char *input)
{
	int		start;
	char	quote;

	start = *ip;
	quote = input[*ip];
	while (input[*ip] && input[*ip] != quote)
		(*ip)++;
	while (input[*ip] && !ft_isspace(input[*ip]) && !is_sep(input[*ip]))
	{
		if (is_quote(input[*ip]))
		{
			quote = input[*ip];
			(*ip)++;
			while (input[*ip] && input[*ip] != quote)
				(*ip)++;
			if (input[*ip] == quote)
				(*ip)++;
		}
		else
			(*ip)++;
	}
	if (quotes_closed(input) == false)
		return (write(2, "minishell: missing closing quote\n", 34), 1);
	add_token_quote(data, WORD, &input[start], *ip - start);
	return (0);
}

static int	tokenize_str(t_data **data, int *ip, char *input)
{
	int	start;

	start = *ip;
	while (input[*ip] && !ft_isspace(input[*ip]) && !is_sep(input[*ip]))
	{
		if (is_quote(input[*ip]))
		{
			*ip = start;
			if (tokenize_quote(data, ip, input))
				return (1);
			return (0);
		}
		(*ip)++;
	}
	add_token(data, WORD, &input[start], *ip - start);
	return (0);
}

static int	tokenize_sep(t_data **data, int *ip, char *input)
{
	int	start;
	int	len;

	start = *ip;
	len = 0;
	if (input[*ip] == '|')
	{
		add_token(data, PIPE, &input[start], 1);
		if (input[*ip + 1] && ft_isspace(input[*ip + 1]) && input[*ip + 2]
			&& input[*ip + 2] == '|')
			add_token(data, WORD, &input[start], 1);
		(*ip)++;
	}
	else if (is_sep(input[*ip]))
	{
		while (input[*ip] && is_sep(input[*ip]) && input[*ip] != '|')
		{
			len++;
			(*ip)++;
		}
		if (len > 2)
			return (syntax_error_msg(&input[start]), 1);
		add_token(data, REDIR, &input[start], len);
	}
	return (0);
}

int	lexer(t_data **data, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (is_sep(input[i]))
		{
			if (tokenize_sep(data, &i, input))
				return (1);
		}
		else
		{
			if (tokenize_str(data, &i, input))
				return (1);
		}
	}
	if (!(*data)->h_tokens)
		return (1);
	return (0);
}
