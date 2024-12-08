/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:44:40 by phautena          #+#    #+#             */
/*   Updated: 2024/12/08 19:09:16 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token(t_token **h_tokens, t_type type, char *str, int len)
{
	t_token	*new_token;
	t_token	*temp;

	if (len <= 0)
		return ;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		mem_error_tokens(h_tokens);
	new_token->value = ft_substr(str, 0, len);
	if (!new_token->value)
		mem_error_tokens(h_tokens);
	new_token->token = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	if (!*h_tokens)
	{
		*h_tokens = new_token;
		return ;
	}
	temp = *h_tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
	new_token->prev = temp;
}

static void	tokenize_sep(t_token **data, int *ip, char *input)
{
	int	start;
	int	len;

	start = *ip;
	len = 0;
	while (input[*ip] && is_sep(input[*ip]))
	{
		len++;
		(*ip)++;
	}
	add_token(data, REDIR, &input[start], len);
}

static int	get_token_length(char *input, int *ip, char quote)
{
	int	len;

	len = 2;
	while (input[*ip] && input[*ip] != quote)
	{
		(*ip)++;
		len++;
		if (input[*ip] == quote && input[*ip + 1] == quote && input[*ip
			+ 2] != quote)
		{
			len += 2;
			(*ip) += 2;
		}
	}
	return (len);
}

static void	tokenize_quote(t_token **data, int *ip, char *input)
{
	char	quote;
	int		start;
	int		len;

	quote = input[*ip];
	start = (*ip)++;
	len = get_token_length(input, ip, quote);
	if (input[*ip] == quote)
	{
		if (quote == '"')
			add_token(data, D_QUOTE, &input[start], len);
		else
			add_token(data, S_QUOTE, &input[start], len);
		(*ip)++;
	}
	else
		ft_putstr_fd("Error: quotes are not closed\n", 2);
}

static void	tokenize_str(t_token **data, int *ip, char *input)
{
	int	start;

	start = *ip;
	while (input[*ip] && !ft_isspace(input[*ip]) && !is_sep(input[*ip])
		&& !is_quote(input[*ip]))
		(*ip)++;
	add_token(data, WORD, &input[start], *ip - start);
}

void	lexer(t_token **data, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (is_quote(input[i]))
			tokenize_quote(data, &i, input);
		else if (is_sep(input[i]))
			tokenize_sep(data, &i, input);
		else
			tokenize_str(data, &i, input);
	}
	print_tokens(*data);
}
