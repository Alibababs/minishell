/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:44:40 by phautena          #+#    #+#             */
/*   Updated: 2024/12/09 13:27:51 by alibabab         ###   ########.fr       */
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

static void	tokenize_quote(t_token **data, int *ip, char *input)
{
	int		start;
	char	quote;

	start = *ip;
	quote = input[*ip];
	while (input[*ip] && input[*ip] != quote)
		(*ip)++;
	if (input[*ip] == quote)
		(*ip)++;
	while (input[*ip] && !ft_isspace(input[*ip]) && !is_sep(input[*ip]))
		(*ip)++;
	if (quotes_closed(input) == true)
		add_token(data, QUOTES, &input[start], *ip - start);
	else
		ft_putstr_fd("Error : Quotes are not closed\n", 2);
}

static void	tokenize_str(t_token **data, int *ip, char *input)
{
	int	start;

	start = *ip;
	while (input[*ip] && !ft_isspace(input[*ip]) && !is_sep(input[*ip]))
	{
		if (is_quote(input[*ip]))
		{
			*ip = start;
			tokenize_quote(data, ip, input);
			return ;
		}
		(*ip)++;
	}
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
		else if (is_sep(input[i]))
			tokenize_sep(data, &i, input);
		else
			tokenize_str(data, &i, input);
	}
	print_tokens(*data);
}
