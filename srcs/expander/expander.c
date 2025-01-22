/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:19:22 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/22 16:26:21 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_useless_quotes(t_data **data, t_token *current)
{
	int		i;
	int		j;
	int		mode;
	char	*res;

	i = 0;
	j = 0;
	mode = 1;
	res = malloc(sizeof(char) * (ft_strlen(current->value) + 1));
	if (!res)
		mem_error(data);
	while (current->value[i])
	{
		if ((current->value[i] == 34 || current->value[i] == 39) && mode == 1)
			mode = current->value[i];
		else if (current->value[i] == mode)
			mode = 1;
		else
			res[j++] = current->value[i];
		i++;
	}
	res[j] = '\0';
	free(current->value);
	current->value = res;
}

static void	remove_useless_dollars(t_data **data, t_token *current)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(current->value) + 1));
	if (!res)
		mem_error(data);
	while (current->value[i])
	{
		if (current->value[i] == '$' && is_quote(current->value[i + 1])
			&& !in_s_quotes(current->value, &current->value[i])
			&& !in_d_quotes(current->value, &current->value[i])
			&& current->value[i + 1] != '=')
			i++;
		else
			res[j++] = current->value[i++];
	}
	res[j] = '\0';
	free(current->value);
	current->value = res;
}

static void	remove_useless_char(t_data **data)
{
	t_token	*temp;

	temp = (*data)->h_tokens;
	while (temp)
	{
		remove_useless_dollars(data, temp);
		remove_useless_quotes(data, temp);
		temp = temp->next;
	}
}

int	expander(t_data **data)
{
	t_token	*temp;

	temp = (*data)->h_tokens;
	while (temp)
	{
		if (ft_strchr(temp->value, '$'))
			temp->value = handle_dollar(temp->value, data);
		temp = temp->next;
	}
	if (remove_empty_tokens(data))
		return (1);
	remove_useless_char(data);
	return (0);
}
