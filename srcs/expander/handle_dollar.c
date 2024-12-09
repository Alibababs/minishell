/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:00:39 by alibabab          #+#    #+#             */
/*   Updated: 2024/12/09 21:09:05 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_len(char *value, t_env **h_env, int i, int *new_len)
{
	int		j;
	char	*var_name;
	char	*var_value;

	j = i + 1;
	while (ft_isalnum(value[j]))
		j++;
	var_name = ft_substr(value, i + 1, j - i - 1);
	var_value = get_var(var_name, h_env);
	if (var_value)
		*new_len += ft_strlen(var_value);
	free(var_name);
	return (j);
}

static int	calculate_new_len(char *value, t_env **h_env)
{
	int	new_len;
	int	i;

	new_len = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && ft_isalnum(value[i + 1]) && value[i - 1] != '\\')
			i = var_len(value, h_env, i, &new_len);
		else
		{
			if (value[i] == '\\' && value[i + 1] == '$')
				new_len++;
			new_len++;
			i++;
		}
	}
	return (new_len);
}

static char	*handle_var_replacement(char *ptr, t_env **h_env, char **new_ptr)
{
	int		j;
	char	*var_name;
	char	*var_value;

	j = 1;
	while (ft_isalnum(ptr[j]))
		j++;
	var_name = ft_substr(ptr, 1, j - 1);
	var_value = get_var(var_name, h_env);
	if (var_value)
	{
		ft_strcpy(*new_ptr, var_value);
		*new_ptr += ft_strlen(var_value);
	}
	free(var_name);
	return (ptr + j);
}

static int	in_backslash(char *ptr, char *start)
{
	int	backslash_count;

	backslash_count = 0;
	ptr--;
	while (ptr >= start && *ptr == '\\')
	{
		backslash_count++;
		ptr--;
	}
	return (backslash_count % 2 != 0);
}

static void	replace_dollars(char *value, t_env **h_env, char *new_value)
{
	char	*new_ptr;
	char	*ptr;

	new_ptr = new_value;
	ptr = value;
	while (*ptr)
	{
		if (*ptr == '$' && ft_isalnum(*(ptr + 1)) && !in_backslash(ptr, value))
			ptr = handle_var_replacement(ptr, h_env, &new_ptr);
		else
		{
			*new_ptr = *ptr;
			new_ptr++;
			ptr++;
		}
	}
	*new_ptr = '\0';
}

char	*handle_dollar(char *value, t_env **h_env)
{
	int		new_len;
	char	*new_value;
	int		i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && in_s_quotes(value, &value[i]))
			return (value);
		i++;
	}
	new_len = calculate_new_len(value, h_env);
	new_value = malloc(new_len + 1);
	if (!new_value)
		mem_error_env(h_env);
	replace_dollars(value, h_env, new_value);
	return (new_value);
}
