/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:50:42 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/16 09:02:52 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	valid_export(char *str)
{
	int	i;

	i = 0;
	if (!isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
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

static void	ft_set_env(t_data **data, char *name, char *value, bool empty_value)
{
	t_env	*temp;

	temp = (*data)->h_env;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			if (!temp->value)
				mem_error(data);
			temp->empty_value = empty_value;
			return ;
		}
		temp = temp->next;
	}
	add_env_end(name, value, data);
	ft_set_env(data, name, value, empty_value);
}

static int	get_name_and_value(char *str, char **name, char **value,
		bool *empty_value, t_data **data)
{
	char	*equals;
	char	*env_value;

	equals = ft_strchr(str, '=');
	if (equals)
	{
		*name = ft_substr(str, 0, equals - str);
		*value = ft_strdup(equals + 1);
		*empty_value = (*value && *value[0] == '\0');
	}
	else
	{
		*name = ft_strdup(str);
		env_value = ft_getenv(*name, data);
		if (env_value)
			*value = ft_strdup(env_value);
		else
			*value = ft_strdup("");
		*empty_value = false;
	}
	return (0);
}

int	ft_export(char **argv, t_data **data)
{
	int		i;
	int		flag;
	char	*name;
	char	*value;
	bool	empty_value;

	flag = 0;
	i = 1;
	if (!argv[1])
		print_export(data);
	else
	{
		while (argv[i])
		{
			get_name_and_value(argv[i], &name, &value, &empty_value, data);
			if (valid_export(name) == false)
				flag = msg_invalid_export(argv[i]);
			else
				ft_set_env(data, name, value, empty_value);
			free(name);
			free(value);
			i++;
		}
	}
	return (flag);
}
