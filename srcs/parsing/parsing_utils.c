/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:10:32 by phautena          #+#    #+#             */
/*   Updated: 2024/11/21 13:49:54 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_is_redir(t_token *current)
{
	if (current->token == IN || current->token == OUT
		|| current->token == APPEND || current->token == HEREDOC)
		return (1);
	else
		return (0);
}

int	is_shitty_redir(t_token *current)
{
	int		i;
	char	*str;

	i = 0;
	str = current->value;
	while (str[i])
	{
		if (str[i] != '<' && str[i] != '>')
			return (0);
		i++;
	}
	return (1);
}
