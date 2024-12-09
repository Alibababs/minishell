/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:58:13 by phautena          #+#    #+#             */
/*   Updated: 2024/12/09 12:58:43 by alibabab         ###   ########.fr       */
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
