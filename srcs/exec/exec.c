/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:00:38 by phautena          #+#    #+#             */
/*   Updated: 2025/01/24 11:44:35 by phautena         ###   ########.fr       */
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
		else if (is_builtin(temp->path))
			g_exit_status = temp->ex_stat;
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
			close(cmd->outfile);
		cmd = cmd->next;
	}
}

static void	check_cmd(t_cmd *cmd, t_data **data)
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

static int	launch_command(t_data **data)
{
	t_cmd	*cmd;

	cmd = (*data)->h_cmds;
	while (cmd)
	{
		if (check_redirs(cmd, data))
			g_exit_status = 1;
		else if (is_builtin(cmd->path))
			launch_builtin(cmd, data);
		else if (cmd->no_cmd == false)
		{
			cmd->pid = fork();
			if (cmd->pid == 0)
			{
				check_cmd(cmd, data);
				make_dup(cmd);
				close_pipes(data);
				execve(cmd->path, cmd->argv, (*data)->envp);
			}
		}
		cmd = cmd->next;
	}
	close_pipes(data);
	wait_for_all(data);
	return (0);
}

int	exec(t_data **data)
{
	init_cmd_nodes(data);
	set_path(data);
	set_argv(data);
	if (init_pipes(data))
		return (1);
	if (init_infiles((*data)->h_tokens, (*data)->h_cmds, data))
		return (130);
	init_outfiles((*data)->h_tokens, (*data)->h_cmds);
	// print_cmds((*data)->h_cmds);
	launch_command(data);
	return (0);
}
