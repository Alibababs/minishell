/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:18:46 by p0ulp1            #+#    #+#             */
/*   Updated: 2025/01/09 16:08:47 by alibaba          ###   ########.fr       */
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
	t_cmd	*temp;

	temp = (*data)->h_cmds;
	while (temp)
	{
		if (temp->to_read > -1 && temp->to_read != 0)
			close(temp->to_read);
		if (temp->to_write > -1 && temp->to_write != 1)
			close(temp->to_write);
		temp = temp->next;
	}
}

static int	exec_now(t_data **data)
{
	t_cmd	*temp;

	temp = (*data)->h_cmds;
	while (temp)
	{
		if (is_builtin(temp->path))
			g_exit_status = exec_builtin(temp, data);
		else
		{
			temp->pid = fork();
			if (temp->pid == 0)
			{
				if (check_cmd(temp, data))
					return (exec_error(temp, data), 127);
				dup2(temp->to_read, STDIN_FILENO);
				dup2(temp->to_write, STDOUT_FILENO);
				close_pipes(data);
				execve(temp->path, temp->argv, (*data)->envp);
			}
		}
		temp = temp->next;
	}
	close_pipes(data);
	wait_for_all(data);
	return (0);
}

static void	init_pipes(t_data *data)
{
	int		nb_pipes;
	int		pipefd[2];
	t_cmd	*cmd;

	nb_pipes = count_cmds(data) - 1;
	cmd = data->h_cmds;
	if (cmd->nb_infiles > 0)
		cmd->to_read = cmd->infiles[cmd->nb_infiles - 1];
	while (nb_pipes > 0)
	{
		if (pipe(pipefd) < 0)
			ft_error("Error initializing pipes\n", &data);
		cmd->to_write = pipefd[1];
		cmd->next->to_read = pipefd[0];
		nb_pipes--;
		cmd = cmd->next;
	}
	if (cmd->nb_outfiles > 0)
		cmd->to_write = cmd->outfiles[cmd->nb_outfiles - 1];
}

int	exec_cmds(t_data **data)
{
	init_pipes(*data);
	if (exec_now(data))
		return (1);
	return (0);
}
