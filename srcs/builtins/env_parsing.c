/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:13:47 by phautena          #+#    #+#             */
/*   Updated: 2024/11/08 11:46:34 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_name(char *var)
{
	int	i;

	if (var[0] != '_' && !ft_isalpha(var[0]))
		return (1);
	i = -1;
	while (var[++i])
	{
		if (var[i] == '=')
			break ;
		else if (!ft_isalpha(var[i]) && !ft_isalnum(var[i]) && var[i] != '_')
			return (2);
	}
	return (0);
}

int	export_var_parsing(char *var)
{
	if (check_name(var))
		return (ft_printf("Incorrect name of env variable\n"));
	return (0);
}

static char	*export_value_quotes(char *var, int i, int mode)
{
	char	quote;
	char	*value;
	int		j;

	if (mode == 1)
		quote = 34;
	else
		quote = 39;
	i++;
	j = i;
	while (var[j] && var[j] != quote)
		j++;
	value = ft_substr(var, i, j - i);
	if (!value)
		return (NULL);
	return (value);
}

char	*export_env_value(char *var)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	i++;
	if (var[i] == 34)
	{
		value = export_value_quotes(var, i, 1);
		return (value);
	}
	else if (var[i] == 39)
	{
		value = export_value_quotes(var, i, 2);
		return (value);
	}
	j = i;
	while (var[j] && !ft_isspace(var[j]))
		j++;
	value = ft_substr(var, i, j - i);
	if (!value)
		return (NULL);
	return (value);
}
