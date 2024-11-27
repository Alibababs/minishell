/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:51:07 by phautena          #+#    #+#             */
/*   Updated: 2024/11/27 16:17:09 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd *current, t_env **h_env)
{
	if (!ft_strncmp(current->path, "cd", 3))
		ft_cd(current->argv);
	else if (!ft_strncmp(current->path, "echo", 3))
		echo(current->argv);
	else if (!ft_strncmp(current->path, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(current->path, "export", 3))
		export_var(current->argv[1], h_env);
	else if (!ft_strncmp(current->path, "unset", 3))
		unset(current->argv[1], h_env);
	else if (!ft_strncmp(current->path, "env", 3))
		print_env(h_env);
	else if (!ft_strncmp(current->path, "exit", 3))
		exit(0);
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
		if (!ft_strncmp(str, builtin[i], ft_strlen(str)))
			return (free(builtin), 1);
		i++;
	}
	free(builtin);
	return (0);
}
