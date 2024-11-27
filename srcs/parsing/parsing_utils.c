/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:10:32 by phautena          #+#    #+#             */
/*   Updated: 2024/11/27 13:02:43 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_pipes(t_token *current)
{
	if (current->next && current->token == PIPE && current->next->token == PIPE)
		return (1);
	return (0);
}

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
	int		len;
	char	*str;

	i = 0;
	str = current->value;
	len = ft_strlen(str);
	if (len > 2)
	{
		while (str[i])
		{
			if (str[i] != '<' && str[i] != '>')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}
