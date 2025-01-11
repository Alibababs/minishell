/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:50:42 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/11 14:30:19 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_export(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (false);
		if (ft_isalpha(str[i]))
			flag++;
		i++;
	}
	if (flag == 0)
		return (false);
	return (true);
}

static void	print_export(t_data **data)
{
	t_env	*temp;

	temp = (*data)->h_env;
	while (temp)
	{
		if (temp->value)
			printf("export %s=\"%s\"\n", temp->name, temp->value);
		else
			printf("export %s\n", temp->name);
		temp = temp->next;
	}
}

static bool	export_exists(char *str, t_data **data)
{
	t_env	*temp;
	char	*name;
	char	*value;

	temp = (*data)->h_env;
	name = parse_env_name(str);
	if (!name)
		mem_error(data);
	value = parse_env_value(str);
	if (!value)
		return (free(name), mem_error(data), false);
	while (temp)
	{
		if (!ft_strcmp(name, temp->name))
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			if (!temp->value)
				return (free(value), free(name), mem_error(data), false);
			return (free(name), free(value), true);
		}
		temp = temp->next;
	}
	return (free(name), false);
}

static void	export_variable(char *str, t_data **data)
{
	char	*name;
	char	*value;

	name = parse_env_name(str);
	if (!name)
		mem_error(data);
	value = parse_env_value(str);
	if (!value)
	{
		free(name);
		mem_error(data);
	}
	if (export_exists(str, data) == true)
		;
	else
		add_env_end(name, value, data);
	free(name);
	free(value);
}

int	ft_export(char **argv, t_data **data)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (!argv[1])
		print_export(data);
	else
	{
		while (argv[++i])
		{
			if (check_export(argv[i]) == false)
			{
				ft_putstr_fd("export: ", 2);
				ft_putstr_fd(argv[1], 2);
				ft_putstr_fd(": not a valid identifier\n", 2);
				flag = 1;
			}
			else
				export_variable(argv[i], data);
		}
	}
	return (flag);
}
