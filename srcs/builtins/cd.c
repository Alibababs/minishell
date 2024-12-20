/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:02:01 by pbailly           #+#    #+#             */
/*   Updated: 2024/12/20 18:55:07 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name, t_data *data)
{
	t_env	*temp;

	if (!name || !data)
		return (NULL);
	temp = data->h_env;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	ft_cd(char **argv, t_data *data)
{
	char	*oldpwd;
	char	*pwd;
	char	*home;
	int		ret;

	if (!argv[1])
	{
		home = getenv("HOME");
		if (!home)
			return (perror("cd"), 1);
		ret = chdir(home);
	}
	else if (!ft_strcmp(argv[1], "-"))
	{
		oldpwd = getenv("OLDPWD");
		if (!oldpwd)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
		ret = chdir(oldpwd);
	}
	else
		ret = chdir(argv[1]);
	if (ret == -1)
		return (perror("cd"), 1);
	oldpwd = getenv("PWD");
	if (oldpwd)
		add_env_end("OLDPWD", oldpwd, &data);
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		add_env_end("PWD", pwd, &data);
		free(pwd);
	}
	else
	{
		perror("getcwd");
		return (1);
	}
	// print_env(&data);
	return (0);
}
