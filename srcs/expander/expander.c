/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:19:22 by alibabab          #+#    #+#             */
/*   Updated: 2024/12/10 14:48:50 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_useless_quotes(t_data *data, t_token *current)
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
		mem_error(&data);
	while (current->value[i])
	{
		if ((current->value[i] == 34 || current->value[i] == 39) && mode == 1)
			mode = current->value[i];
		else if (current->value[i] == mode)
			mode = 1;
		else
		{
			res[j] = current->value[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	free(current->value);
	current->value = res;
}

static int	quote_before(char *value, int i)
{
	int	len;
	int	j;

	len = ft_strlen(value);
	j = 0;
	while (value[j])
	{
		if (value[j] == '$' && j == 0)
			return (0);
		j++;
	}
	if (value[i - 1])
	{
		if (value[i - 1] == 34 || value[i - 1] == 39)
			return (1);
	}
	return (0);
}

static void	remove_useless_dollars(t_data *data, t_token *current)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(current->value) + 1));
	if (!res)
		mem_error(&data);
	while (current->value[i])
	{
		if (current->value[i] == '$' && !quote_before(current->value, i) && current->value[i + 1] != '=')
			i++;
		else
		{
			res[j] = current->value[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
	free(current->value);
	current->value = res;
}

static void	remove_useless_char(t_data *data)
{
	t_token	*temp;

	temp = data->h_tokens;
	while (temp)
	{
		remove_useless_dollars(data, temp);
		remove_useless_quotes(data, temp);
		temp = temp->next;
	}
}

void	expander(t_data *data)
{
	t_token	*temp;

	temp = data->h_tokens;
	while (temp)
	{
		if (ft_strstr(temp->value, "$?"))
			temp->value = handle_exit_status(temp->value, data);
		else if (ft_strchr(temp->value, '$'))
			temp->value = handle_dollar(temp->value, data);
		temp = temp->next;
	}
	remove_empty_tokens(data);
	remove_useless_char(data);
	print_tokens(data->h_tokens);
}
