/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:02:01 by pbailly           #+#    #+#             */
/*   Updated: 2025/01/16 12:53:44 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd(t_data **data, char *old_pwd, char *new_pwd)
{
	ft_set_env(data, "OLDPWD", old_pwd, false);
	ft_set_env(data, "PWD", new_pwd, false);
	free(old_pwd);
	free(new_pwd);
	return (0);
}

int	ft_cd(char **argv, t_data **data)
{
	int		ret;
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

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
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (mem_error(data), 1);
	ret = chdir(path);
	if (ret == -1)
		return (perror("minishell: cd"), 1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (mem_error(data), 1);
	return (update_pwd(data, old_pwd, new_pwd));
}
