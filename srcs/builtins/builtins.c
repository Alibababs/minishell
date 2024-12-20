/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:35:28 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/20 16:54:57 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd *cmd, t_data *data)
{
	if (!ft_strcmp(cmd->path, "cd"))
	{
		if (ft_cd(cmd->argv, data))
			return (1);
	}
	else if (!ft_strcmp(cmd->path, "echo"))
		ft_echo(cmd->argv);
	else if (!ft_strcmp(cmd->path, "pwd"))
		ft_pwd();
	// else if (!ft_strcmp(cmd->path, "export"))
	// 	export_var(cmd, data);
	// else if (!ft_strcmp(cmd->path, "unset"))
	// 	unset(cmd, data);
	else if (!ft_strcmp(cmd->path, "env"))
		ft_env(data);
	else if (!ft_strcmp(cmd->path, "exit"))
	{
		if (ft_exit(cmd->argv))
			return (1);
	}
	return (0);
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
