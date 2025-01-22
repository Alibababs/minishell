/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:58:13 by phautena          #+#    #+#             */
/*   Updated: 2025/01/22 16:49:19 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool	quotes_closed(char *input)
{
	int	i;
	int	flag;

	i = 0;
	flag = -1;
	while (input[i])
	{
		if (input[i] == 34 && flag == -1)
			flag = 1;
		else if (input[i] == 34 && flag == 1)
			flag = -1;
		else if (input[i] == 39 && flag == -1)
			flag = 2;
		else if (input[i] == 39 && flag == 2)
			flag = -1;
		i++;
	}
	if (flag != -1)
		return (false);
	return (true);
}

void	add_token_quote(t_data **data, t_type type, char *str, int len)
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
	new_token->was_quote = true;
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
