/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:56:00 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/24 11:47:52 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_builtin(t_cmd *cmd, t_data **data, int save, int save2)
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
		return (ft_exit(cmd->argv, data, save, save2));
	return (1);
}

char	*ft_getenv(char *name, t_data **data)
{
	t_env	*temp;

	if (!name || !data)
		return (NULL);
	temp = (*data)->h_env;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	ft_set_env(t_data **data, char *name, char *value, bool empty_value)
{
	t_env	*temp;

	temp = (*data)->h_env;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			if (!temp->value)
				mem_error(data);
			temp->empty_value = empty_value;
			return ;
		}
		temp = temp->next;
	}
	add_env_end(name, value, data);
	ft_set_env(data, name, value, empty_value);
}

void	launch_builtin(t_cmd *cmd, t_data **data)
{
	int	save;
	int	save2;

	save = dup(STDOUT_FILENO);
	if (cmd->outfile != -2)
		dup2(cmd->outfile, STDOUT_FILENO);
	else if (cmd->to_write > 2)
		dup2(cmd->to_write, STDOUT_FILENO);
	save2 = dup(STDIN_FILENO);
	if (cmd->infile != -2)
		dup2(cmd->infile, STDIN_FILENO);
	else if (cmd->to_read > 2)
		dup2(cmd->infile, STDIN_FILENO);
	g_exit_status = exec_builtin(cmd, data, save, save2);
	if (cmd->ex_stat == -1)
		cmd->ex_stat = g_exit_status;
	dup2(save, STDOUT_FILENO);
	dup2(save2, STDIN_FILENO);
	close(save);
	close(save2);
}
