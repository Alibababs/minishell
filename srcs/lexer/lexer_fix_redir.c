/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fix_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:22:15 by phautena          #+#    #+#             */
/*   Updated: 2024/11/08 11:39:44 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	fix_redir_list(t_token **head)
{
	t_token	*temp;

	temp = *head;
	while (temp->next)
	{
		if (!is_redir(temp->value) && !is_redir(temp->next->value))
		{
			add_redir(&temp);
			del_next_redir(&temp);
			temp = *head;
		}
		else if (temp->next->value[0] == ' ')
		{
			del_next_redir(&temp);
			temp = *head;
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
