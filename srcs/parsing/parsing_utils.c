/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:10:32 by phautena          #+#    #+#             */
/*   Updated: 2024/11/28 14:44:25 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(t_token *current)
{
	int		i;
	int		j;
	char	*old;
	char	*res;

	i = 0;
	j = 0;
	old = current->value;
	res = malloc(sizeof(char) * (ft_strlen(current->value) + 1));
	while (old[i])
	{
		if (old[i] == 34 || old[i] == 39)
			i++;
		else
		{
			res[j] = old[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
	free(current->value);
	current->value = res;
}

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
