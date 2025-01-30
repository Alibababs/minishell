/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:39:21 by ubuntu            #+#    #+#             */
/*   Updated: 2025/01/28 14:36:30 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_builtin(t_cmd *cmd, t_data **data)
{
	int	save;
	int	save2;

	if (is_builtin(cmd->path) && !cmd->prev && !cmd->next && !cmd->no_cmd)
	{
		save = dup(STDOUT_FILENO);
		save2 = dup(STDIN_FILENO);
		if (cmd->outfile != -2)
			dup2(cmd->outfile, STDOUT_FILENO);
		else if (cmd->to_write > 2)
			dup2(cmd->to_write, STDOUT_FILENO);
		if (cmd->infile != -2)
			dup2(cmd->infile, STDIN_FILENO);
		else if (cmd->to_read > 2)
			dup2(cmd->to_read, STDIN_FILENO);
		g_exit_status = exec_builtin(cmd, data, save, save2);
		dup2(save, STDOUT_FILENO);
		dup2(save2, STDIN_FILENO);
		close(save);
		close(save2);
		return (1);
	}
	return (0);
}

void	child_process(t_cmd *cmd, t_data **data)
{
	int	builtin_exit;

	if (is_builtin(cmd->path))
	{
		make_dup(cmd);
		close_pipes(data);
		builtin_exit = exec_builtin(cmd, data, 0, 0);
		exit(builtin_exit);
	}
	else
	{
		check_cmd(cmd, data);
		make_dup(cmd);
		close_pipes(data);
		execve(cmd->path, cmd->argv, (*data)->envp);
	}
}

void	start_exec(t_data **data)
{
	t_cmd	*cmd;

	cmd = (*data)->h_cmds;
	if (single_builtin(cmd, data))
		return ;
	while (cmd)
	{
		if (cmd->no_cmd == false)
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
				child_process(cmd, data);
			else if (cmd->pid == -1)
				fork_error(data);
		}
		cmd = cmd->next;
	}
	close_pipes(data);
	wait_for_all(data);
}
