/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:02:01 by pbailly           #+#    #+#             */
/*   Updated: 2025/01/09 12:45:44 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getenv(char *name, t_data **data)
{
	t_env	*temp;

	if (!name || !data)
		return (NULL);
	temp = (*data)->h_env;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

// static int	update_pwd(t_data *data, char *new_pwd)
// {
// 	t_env	*temp;

// 	temp = data->h_env;
// 	while (temp)
// 	{
// 		if (!ft_strcmp(temp->name, "PWD"))
// 		{
// 			free(temp->value);
// 			temp->value = ft_strdup(new_pwd);
// 			if (!temp->value)
// 				mem_error(&data);
// 			return (0);
// 		}
// 		temp = temp->next;
// 	}
// 	return (0);
// }

int	ft_cd(char **argv, t_data **data)
{
	int		ret;
	char	*path;

	// char	*oldpwd;
	if (argv[1] && argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (!argv[1])
	{
		path = ft_getenv("HOME", data);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else
		path = argv[1];
	// oldpwd = ft_getenv("PWD", data);
	// Another way is possible... Long live export
	// if (oldpwd)
	// add_env_end("OLDPWD", oldpwd, &data);
	ret = chdir(path);
	if (ret == -1)
		return (perror("minishell: cd"), 1);
	path = getcwd(NULL, 0);
	if (!path)
		return (perror("getcwd"), 1);
	// update_pwd(data, path);
	free(path);
	return (0);
}
