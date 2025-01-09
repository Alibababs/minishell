/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:35:28 by p0ulp1            #+#    #+#             */
/*   Updated: 2025/01/09 15:05:17 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd *cmd, t_data **data)
{
	if (!ft_strcmp(cmd->path, "cd"))
		return (ft_cd(cmd->argv, data));
	else if (!ft_strcmp(cmd->path, "echo"))
		return (ft_echo(cmd->argv), 0);
	else if (!ft_strcmp(cmd->path, "pwd"))
		return (ft_pwd(), 0);
	else if (!ft_strcmp(cmd->path, "export"))
		return (ft_export(cmd->argv, data));
	else if (!ft_strcmp(cmd->path, "unset"))
		return (ft_unset(cmd->argv, data), 0);
	else if (!ft_strcmp(cmd->path, "env"))
		return (ft_env(data), 0);
	else if (!ft_strcmp(cmd->path, "exit"))
		return (ft_exit(cmd->argv));
	return (1);
}
