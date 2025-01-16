/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:00:38 by phautena          #+#    #+#             */
/*   Updated: 2025/01/16 15:45:21 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_all(t_data **data)
{
	t_cmd	*temp;
	int		status;

	temp = (*data)->h_cmds;
	while (temp)
	{
		if (temp->pid > -1)
		{
			waitpid(temp->pid, &status, 0);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		temp = temp->next;
	}
}

static void	close_pipes(t_data **data)
{
	t_cmd	*cmd;

	cmd =(*data)->h_cmds;
	while (cmd)
	{
		if (cmd->to_read > 2)
			close(cmd->to_read);
		if (cmd->to_write > 2)
			close(cmd->to_write);
		cmd = cmd->next;
	}
}

static void	check_cmd(t_cmd *cmd,t_data **data)
{
	if (access(cmd->path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->path, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_data(data);
		g_exit_status = 127;
		exit(127);
	}
}

static int	launch_command(t_data **data)
{
	t_cmd	*cmd;

	cmd = (*data)->h_cmds;
	while (cmd)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			if (is_builtin(cmd->path))
				launch_builtin(cmd, data);
			check_cmd(cmd, data);
			make_dup(cmd);
			close_pipes(data);
			execve(cmd->path, cmd->argv, (*data)->envp);
		}
		cmd = cmd->next;
	}
	close_pipes(data);
	wait_for_all(data);
	return (0);
}


int	exec(t_data **data)
{
	int	flag;

	flag = 0;
	init_cmd_nodes(data);
	set_path(data);
	set_argv(data);
	if (init_pipes(data))
		return (1);
	flag += init_infiles(data);
	flag += init_outfiles(data);
	if (flag > 0)
		return (1);
	// print_cmds((*data)->h_cmds);
	launch_command(data);
	return (0);
}
