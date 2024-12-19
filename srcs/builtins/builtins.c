/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:35:28 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/19 22:20:40 by pbailly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// Only the function's prototype, need to add the actual builtins.

int	exec_builtin(t_cmd *cmd, t_data *data)
{
	if (!ft_strcmp(cmd->path, "cd"))
		ft_cd(cmd, data);
	else if (!ft_strcmp(cmd->path, "echo"))
		ft_echo(cmd, data);
	else if (!ft_strcmp(cmd->path, "pwd"))
		ft_pwd(cmd, data);
	// else if (!ft_strcmp(cmd->path, "export"))
	// 	export_var(cmd, data);
	// else if (!ft_strcmp(cmd->path, "unset"))
	// 	unset(cmd, data);
	// else if (!ft_strcmp(cmd->path, "env"))
	// 	print_env(data);
	else if (!ft_strcmp(cmd->path, "exit"))
		ft_exit(cmd, data);
	return (0);
}

void	ft_cd(t_cmd *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	printf("CD builtin\n");
	return ;
}

void	ft_pwd(t_cmd *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	printf("pwd builtin\n");
	return ;
}

void	ft_export(t_cmd *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	printf("export builtin\n");
	return ;
}

void	ft_unset(t_cmd *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	printf("unset builtin\n");
	return ;
}

void	ft_env(t_cmd *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	printf("env builtin\n");
	return ;
}

void	ft_exit(t_cmd *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	printf("exit builtin\n");
	return ;
}
