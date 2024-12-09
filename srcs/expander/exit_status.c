/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:45:03 by alibabab          #+#    #+#             */
/*   Updated: 2024/12/09 16:57:24 by alibabab         ###   ########.fr       */
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
		if (value[i] == '$' && value[i + 1] == '?')
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

static void	process_exit_status(char *value, char *status_str, char *new_value,
		char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '$' && ptr[i + 1] == '?' && !in_single_quotes(value,
				&ptr[i]))
		{
			ft_strcpy(new_value, status_str);
			new_value += ft_strlen(status_str);
			i += 2;
		}
		else
		{
			*new_value = ptr[i];
			new_value++;
			i++;
		}
	}
	*new_value = '\0';
}

char	*handle_exit_status(char *value, t_token **h_token)
{
	char	*status_str;
	char	*new_value;
	char	*ptr;

	status_str = ft_itoa(g_exit_status);
	new_value = malloc(get_new_len(value, ft_strlen(status_str)) + 1);
	if (!new_value)
		mem_error_tokens(h_token);
	ptr = value;
	process_exit_status(value, status_str, new_value, ptr);
	return (new_value);
}
