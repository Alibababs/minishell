/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:50:42 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/15 20:57:53 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	valid_export(char *str)
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
		if (temp->value && *temp->value)
			printf("export %s=\"%s\"\n", temp->name, temp->value);
		else
			printf("export %s\n", temp->name);
		temp = temp->next;
	}
}

static void	ft_set_env(t_data **data, char *name, char *value)
{
	char	*env_value;

	env_value = ft_getenv(name, data);
	if (env_value)
	{
		free(env_value);
		env_value = ft_strdup(value);
		if (!env_value)
			mem_error(data);
	}
	else
		add_env_end(name, value, data);
}

static int	get_name_and_value(char *str, char **name, char **value,
		t_data **data)
{
	char	*equals;
	char	*env_value;

	equals = ft_strchr(str, '=');
	if (equals)
	{
		*name = ft_substr(str, 0, equals - str);
		*value = ft_strdup(equals + 1);
	}
	else
	{
		*name = ft_strdup(str);
		env_value = ft_getenv(*name, data);
		if (env_value)
			*value = ft_strdup(env_value);
		else
			*value = ft_strdup("");
	}
	return (0);
}

int	ft_export(char **argv, t_data **data)
{
	int		i;
	int		flag;
	char	*name;
	char	*value;

	flag = 0;
	i = 1;
	if (!argv[1])
		print_export(data);
	else
	{
		while (argv[i])
		{
			get_name_and_value(argv[i], &name, &value, data);
			if (valid_export(name) == false)
				flag = msg_invalid_export(argv[i]);
			else
				ft_set_env(data, name, value);
			free(name);
			free(value);
			i++;
		}
	}
	return (flag);
}
