/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fix_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:22:15 by phautena          #+#    #+#             */
/*   Updated: 2024/12/02 12:27:09 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	all_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	add_redir(t_token **current)
{
	t_token	*temp;
	char	*fixed;

	temp = *current;
	fixed = ft_strjoin(temp->value, temp->next->value);
	if (!fixed)
		return ;
	free(temp->value);
	temp->value = fixed;
}

static int	is_redir(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] != '<' && value[i] != '>')
			return (1);
		i++;
	}
	return (0);
}

void	fix_redir_list(t_token **h_token)
{
	t_token	*temp;

	temp = *h_token;
	while (temp && temp->next)
	{
		if (!is_redir(temp->value) && !is_redir(temp->next->value))
		{
			add_redir(&temp);
			del_next_redir(&temp);
			temp = *h_token;
		}
		else
			temp = temp->next;
	}
}

void	del_next_redir(t_token **current)
{
	t_token	*temp;

	temp = *current;
	temp = temp->next;
	if (temp->next)
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	else
		temp->prev->next = NULL;
	if (temp->value)
		free(temp->value);
	free(temp);
}
