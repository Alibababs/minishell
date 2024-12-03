/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:51:07 by phautena          #+#    #+#             */
/*   Updated: 2024/12/03 14:01:08 by pbailly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd *current, t_env **h_env)
{
	if (!ft_strcmp(current->path, "cd"))
		ft_cd(current->argv);
	else if (!ft_strcmp(current->path, "echo"))
		ft_echo(current->argv);
	else if (!ft_strcmp(current->path, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(current->path, "export"))
		export_var(current->argv[1], h_env);
	else if (!ft_strcmp(current->path, "unset"))
		unset(current->argv[1], h_env);
	else if (!ft_strcmp(current->path, "env"))
		print_env(h_env);
	else if (!ft_strcmp(current->path, "exit"))
		ft_exit(current->argv);
	return (0);
}

int	exec_is_builtin(char *str)
{
	char	**builtin;
	int		i;

	builtin = declare_builtin();
	if (!builtin)
		return (2);
	i = 0;
	while (builtin[i])
	{
		if (!ft_strcmp(str, builtin[i]))
			return (free(builtin), 1);
		i++;
	}
	free(builtin);
	return (0);
}
