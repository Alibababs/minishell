/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:32:55 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/18 17:44:49 by p0ulp1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd *cmd, t_data *data)
{
	if (!ft_strcmp(cmd->path, "cd"))
		ft_cd(cmd, data);
	else if (!ft_strcmp(cmd->path, "echo"))
		ft_echo(cmd, data);
	else if (!ft_strcmp(cmd->path, "pwd"))
		ft_pwd(cmd, data);
	else if (!ft_strcmp(cmd->path, "export"))
		export_var(cmd, data);
	else if (!ft_strcmp(cmd->path, "unset"))
		unset(cmd, data);
	else if (!ft_strcmp(cmd->path, "env"))
		print_env(data);
	else if (!ft_strcmp(cmd->path, "exit"))
		ft_exit(cmd, data);
	return (0);
}
