/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:00:39 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/22 16:32:49 by alibabab         ###   ########.fr       */
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
	while (ft_isalnum(value[j]) || value[j] == '_')
		j++;
	var_name = ft_substr(value, i + 1, j - i - 1);
	var_value = get_var(var_name, data);
	if (var_value)
		*new_len += ft_strlen(var_value);
	free(var_name);
	return (j);
}

static int	calculate_new_len(char *value, t_data **data, char *exit_status)
{
	int	new_len;
	int	i;

	new_len = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && !in_s_quotes(value, &value[i]))
		{
			if (value[i + 1] == '?')
			{
				new_len += ft_strlen(exit_status);
				i += 2;
			}
			else if (ft_isalnum(value[i + 1]) || value[i + 1] == '_')
				i = var_len(value, data, i, &new_len);
			else
				new_len += (0 + ++i);
		}
		else
			new_len += (0 + ++i);
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
	while (ft_isalnum(value[j]) || value[j] == '_')
		j++;
	var_name = ft_substr(value, 1, j - 1);
	var_value = get_var(var_name, data);
	if (var_value)
	{
		ft_strlcpy(*new_value, var_value, ft_strlen(var_value) + 1);
		*new_value += ft_strlen(var_value);
	}
	free(var_name);
	return (value + j);
}

static void	replace_dollars_and_exit_status(char *value, t_data **data,
		char *new_value, char *exit_status)
{
	char	*ptr;

	ptr = value;
	while (*ptr)
	{
		if (*ptr == '$' && !in_s_quotes(value, ptr))
		{
			if (*(ptr + 1) == '?')
			{
				ft_strlcpy(new_value, exit_status, ft_strlen(exit_status) + 1);
				new_value += ft_strlen(exit_status);
				ptr += 2;
			}
			else if (ft_isalnum(*(ptr + 1)) || *(ptr + 1) == '_')
				ptr = handle_var_replacement(ptr, data, &new_value);
			else
				*(new_value++) = *(ptr++);
		}
		else
			*(new_value++) = *(ptr++);
	}
	*new_value = '\0';
}

char	*handle_dollar(char *value, t_data **data)
{
	char	*exit_status;
	int		new_len;
	char	*new_value;

	exit_status = ft_itoa(g_exit_status);
	new_len = calculate_new_len(value, data, exit_status);
	new_value = malloc(new_len + 1);
	if (!new_value)
	{
		free(exit_status);
		mem_error(data);
	}
	replace_dollars_and_exit_status(value, data, new_value, exit_status);
	free(exit_status);
	free(value);
	return (new_value);
}
