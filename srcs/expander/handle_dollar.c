/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:00:39 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/22 16:03:32 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_len(char *value, t_data **data, int i, int *new_len)
{
	int		j;
	char	*var_name;
	char	*var_value;

	j = i + 1;
	if (ft_isdigit(value[j]))
		return (j + 1);
	while (ft_isalnum(value[j]))
		j++;
	var_name = ft_substr(value, i + 1, j - i - 1);
	var_value = get_var(var_name, data);
	if (var_value)
		*new_len += ft_strlen(var_value);
	free(var_name);
	return (j);
}

static int	calculate_new_len(char *value, t_data **data)
{
	int	new_len;
	int	i;

	new_len = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && !in_s_quotes(value, &value[i])
			&& (ft_isalnum(value[i + 1]) || value[i + 1] == '_'))
			i = var_len(value, data, i, &new_len);
		else
		{
			new_len++;
			i++;
		}
	}
	return (new_len);
}

static char	*handle_var_replacement(char *value, t_data **data,
		char **new_value)
{
	int		j;
	char	*var_name;
	char	*var_value;

	if (ft_isdigit(value[1]))
		return (value + 2);
	j = 1;
	while (ft_isalnum(value[j]))
		j++;
	var_name = ft_substr(value, 1, j - 1);
	var_value = get_var(var_name, data);
	if (var_value)
	{
		ft_strcpy(*new_value, var_value);
		*new_value += ft_strlen(var_value);
	}
	free(var_name);
	return (value + j);
}

static void	replace_dollars(char *value, t_data **data, char *new_value)
{
	char	*ptr;

	ptr = value;
	while (*ptr)
	{
		if (*ptr == '$' && !in_s_quotes(value, ptr) && (ft_isalnum(*(ptr + 1))
				|| *(ptr + 1) == '_'))
			ptr = handle_var_replacement(ptr, data, &new_value);
		else
		{
			*new_value = *ptr;
			new_value++;
			ptr++;
		}
	}
	*new_value = '\0';
}

char	*handle_dollar(char *value, t_data **data)
{
	int		new_len;
	char	*new_value;

	new_len = calculate_new_len(value, data);
	new_value = malloc(new_len + 1);
	if (!new_value)
		mem_error(data);
	replace_dollars(value, data, new_value);
	free(value);
	return (new_value);
}
