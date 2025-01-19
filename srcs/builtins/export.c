/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:50:42 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/19 15:07:35 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	msg_invalid_export(char *str)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static bool	valid_export(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	print_export(t_data **data)
{
	t_env	*temp;

	temp = (*data)->h_env;
	while (temp)
	{
		if (temp->value && *temp->value)
			printf("export %s=\"%s\"\n", temp->name, temp->value);
		else if (temp->empty_value == true)
			printf("export %s=\"\"\n", temp->name);
		else
			printf("export %s\n", temp->name);
		temp = temp->next;
	}
}

static int	get_name_and_value(char *str, t_export_info *info)
{
	char	*equals;
	char	*env_value;

	equals = ft_strchr(str, '=');
	if (equals)
	{
		info->name = ft_substr(str, 0, equals - str);
		info->value = ft_strdup(equals + 1);
		info->empty_value = (info->value && *info->value == '\0');
	}
	else
	{
		info->name = ft_strdup(str);
		env_value = ft_getenv(info->name, info->data);
		if (env_value)
			info->value = ft_strdup(env_value);
		else
			info->value = ft_strdup("");
		info->empty_value = false;
	}
	return (0);
}

int	ft_export(char **argv, t_data **data)
{
	int				i;
	int				flag;
	t_export_info	info;

	flag = 0;
	i = 1;
	info.data = data;
	if (!argv[1])
		print_export(data);
	else
	{
		while (argv[i])
		{
			get_name_and_value(argv[i], &info);
			if (valid_export(info.name) == false)
				flag = msg_invalid_export(argv[i]);
			else if (ft_strchr(argv[i], '=') || !ft_getenv(info.name, data))
				ft_set_env(data, info.name, info.value, info.empty_value);
			free(info.name);
			free(info.value);
			i++;
		}
	}
	return (flag);
}
