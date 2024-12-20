/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:02:01 by pbailly           #+#    #+#             */
/*   Updated: 2024/12/20 15:09:42 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **argv, t_data *data)
{
	char	*oldpwd;
	t_env	*env;
	int		ret;

	env = data->h_env;
	if (!argv[1])
	{
		while (env)
		{
			if (!ft_strcmp(env->name, "HOME"))
			{
				if (chdir(env->value) == -1)
				{
					perror("cd");
					return (1);
				}
				return (0);
			}
			env = env->next;
		}
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (!ft_strcmp(argv[1], "-"))
	{
		while (env)
		{
			if (!ft_strcmp(env->name, "OLDPWD"))
			{
				if (chdir(env->value) == -1)
				{
					perror("cd");
					return (1);
				}
				printf("%s\n", env->value);
				return (0);
			}
			env = env->next;
		}
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	ret = chdir(argv[1]);
	if (ret == -1)
	{
		perror("cd");
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		return (1);
	}
	while (env)
	{
		if (!ft_strcmp(env->name, "PWD"))
		{
			free(env->value);
			env->value = getcwd(NULL, 0);
			break ;
		}
		env = env->next;
	}
	add_env_end("OLDPWD", oldpwd, &data);
	free(oldpwd);
	return (0);
}
