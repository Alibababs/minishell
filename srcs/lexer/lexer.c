/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:44:40 by phautena          #+#    #+#             */
/*   Updated: 2024/12/05 13:17:32 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_sep(char c)
{
	if (c == '|')
		return (1);
	else if (c == '>' || c == '<')
		return (1);
	return (0);
}

static void	tokenize_sep(t_data **data, int *ip, char *input)
{
	char	*res;
	int		start;
	int		len;

	start = *ip;
	len = 0;
	while (input[*ip] && is_sep(input[*ip]))
	{
		len++;
		(*ip)++;
	}
	res = ft_substr(input, start, len);
	if (!res)
		mem_error(data);
	printf("sep: [%s]\n", res);
}

static void	tokenize_str(t_data **data, int *ip, char *input)
{
	char	*res;
	int		start;
	int		len;

	start = *ip;
	len = 0;
	while (input[*ip] && !is_sep(input[*ip]) && !ft_isspace(input[*ip]))
	{
		len++;
		(*ip)++;
	}
	res = ft_substr(input, start, len);
	if (!res)
		mem_error(data);
	printf("str: [%s]\n", res);
}

static void	tokenize_quote(t_data **data, int *ip, char *input)
{
	char	*res;
	int		start;
	int		len;
	int		quote;

	if (input[*ip] == '"')
		quote = 34;
	else
		quote = 39;
	start = *ip;
	len = 0;
	(*ip)++;
	while (input[*ip] && input[*ip] != quote)
	{
		len++;
		(*ip)++;
	}
	res = ft_substr(input, start, len + 2);
	if (!res)
		mem_error(data);
	(*ip)++;
	printf("quote: [%s]\n", res);
}

static void	split_input(t_data **data, char *input)
{
	int	i;
	int	*ip;

	i = 0;
	ip = &i;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == 39 || input[i] == 34)
			tokenize_quote(data, ip, input);
		else if (is_sep(input[i]))
			tokenize_sep(data, ip, input);
		else
			tokenize_str(data, ip, input);
	}
}

void	lexer(t_data **data, char *input)
{
	if (quotes_closed(input) == false)
		return (ft_error(data, "Please fix your quotes\n"));
	split_input(data, input);
}
