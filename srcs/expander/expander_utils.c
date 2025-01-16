/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:57:17 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/16 14:22:02 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *value, t_data **data)
{
	t_env	*temp;
	char	*var_name;

	var_name = value;
	temp = (*data)->h_env;
	while (temp)
	{
		if (!ft_strcmp(var_name, temp->name))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	in_s_quotes(char *str, char *ptr)
{
	int	in_single_quote;
	int	in_double_quote;
	int	i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (str[i] && &str[i] < ptr)
	{
		if (str[i] == '"')
		{
			if (!in_single_quote)
				in_double_quote = !in_double_quote;
		}
		else if (str[i] == '\'')
		{
			if (!in_double_quote)
				in_single_quote = !in_single_quote;
		}
		i++;
	}
	return (in_single_quote);
}

int	in_d_quotes(char *str, char *ptr)
{
	int	in_single_quote;
	int	in_double_quote;
	int	i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (str[i] && &str[i] < ptr)
	{
		if (str[i] == '"')
		{
			if (!in_single_quote)
				in_double_quote = !in_double_quote;
		}
		else if (str[i] == '\'')
		{
			if (!in_double_quote)
				in_single_quote = !in_single_quote;
		}
		i++;
	}
	return (in_double_quote);
}

static void	remove_empty_tokens_utils(t_data **data, t_token *prev,
		t_token *temp)
{
	if (prev != NULL)
		prev->next = temp->next;
	else
		(*data)->h_tokens = temp->next;
	free(temp->value);
	free(temp);
}

int	remove_empty_tokens(t_data **data)
{
	t_token	*temp;
	t_token	*prev;

	temp = (*data)->h_tokens;
	prev = NULL;
	while (temp != NULL)
	{
		if (temp->value == NULL || temp->value[0] == '\0')
		{
			remove_empty_tokens_utils(data, prev, temp);
			if (prev != NULL)
				temp = prev->next;
			else
				temp = (*data)->h_tokens;
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
	temp = (*data)->h_tokens;
	if (temp == NULL)
		return (1);
	return (0);
}
