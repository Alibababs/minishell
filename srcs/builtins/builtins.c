/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:35:28 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/18 17:46:18 by p0ulp1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///Only the function's prototype, need to add the actual builtins.

void	ft_cd(t_cmd *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	printf("CD builtin\n");
	return ;
}

void	ft_echo(t_cmd *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	printf("echo builtin\n");
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
