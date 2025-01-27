/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:00:38 by phautena          #+#    #+#             */
/*   Updated: 2025/01/27 10:22:53 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_all(t_data **data)
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
		else if (check_redirs(temp, data))
			g_exit_status = 1;
		temp = temp->next;
	}
}

void	close_pipes(t_data **data)
{
	t_cmd	*cmd;

	cmd = (*data)->h_cmds;
	while (cmd)
	{
		if (cmd->to_read > 2)
			close(cmd->to_read);
		if (cmd->to_write > 2)
			close(cmd->to_write);
		if (cmd->infile > -1)
			close(cmd->infile);
		if (cmd->outfile > -1)
		{
			close(cmd->outfile);
			cmd->outfile = -1;
		}
		cmd = cmd->next;
	}
}

void	check_cmd(t_cmd *cmd, t_data **data)
{
	struct stat	path_stat;

	if (ft_strchr(cmd->path, '/'))
	{
		if (access(cmd->path, F_OK) == -1)
		{
			ft_put_error(cmd->path, ": No such file or directory\n");
			free_data(data);
			exit(127);
		}
		else if (access(cmd->path, X_OK) == -1)
		{
			ft_put_error(cmd->path, ": Permission denied\n");
			free_data(data);
			exit(126);
		}
	}
	if (access(cmd->path, X_OK) == -1 || (!stat(cmd->path, &path_stat)
			&& S_ISDIR(path_stat.st_mode)))
	{
		ft_put_error(cmd->path, ": command not found\n");
		free_data(data);
		exit(127);
	}
}

int	exec(t_data **data)
{
	init_cmd_nodes(data);
	set_path(data);
	set_argv(data);
	if (init_pipes(data))
		return (1);
	init_redirections(data);
	// print_cmds((*data)->h_cmds);
	start_exec(data);
	return (0);
}
