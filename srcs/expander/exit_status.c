/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:45:03 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/22 15:56:20 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_new_len(char *value, int status_len)
{
	int	new_len;
	int	i;

	new_len = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?' && !in_s_quotes(value,
				&value[i]))
		{
			new_len += status_len;
			i += 2;
		}
		else
		{
			new_len++;
			i++;
		}
	}
	return (new_len);
}

static void	process_exit_status(char *status_str, char *new_value, char *ptr)
{
	int	i;
	int	new_i;

	i = 0;
	new_i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '$' && ptr[i + 1] == '?' && !in_s_quotes(ptr, &ptr[i]))
		{
			ft_strlcpy(&new_value[new_i], status_str, ft_strlen(status_str)
				+ 1);
			new_i += ft_strlen(status_str);
			i += 2;
		}
		else
		{
			new_value[new_i] = ptr[i];
			new_i++;
			i++;
		}
	}
	new_value[new_i] = '\0';
}

char	*handle_exit_status(char *value, t_data **data)
{
	char	*status_str;
	char	*new_value;

	status_str = ft_itoa(g_exit_status);
	new_value = malloc(get_new_len(value, ft_strlen(status_str)) + 1);
	if (!new_value)
		mem_error(data);
	process_exit_status(status_str, new_value, value);
	free(status_str);
	free(value);
	return (new_value);
}
