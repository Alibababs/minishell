/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:18:46 by p0ulp1            #+#    #+#             */
/*   Updated: 2025/01/07 17:30:33 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_all(t_data **data)
{
	t_cmd	*temp;

	temp = (*data)->h_cmds;
	while (temp)
	{
		if (temp->pid > -1)
			waitpid(temp->pid, NULL, 0);
		temp = temp->next;
	}
}

static void	close_pipes(t_data **data)
{
	t_cmd	*temp;

	temp = (*data)->h_cmds;
	while (temp)
	{
		// if (temp->to_read > -1)
		if (temp->to_read > -1 && temp->to_read != 0)
			close(temp->to_read);
		// if (temp->to_write > -1)
		if (temp->to_write > -1 && temp->to_write != 1)
			close(temp->to_write);
		temp = temp->next;
	}
}

static int	exec_now(t_data **data)
{
	t_cmd		*temp;

	temp = (*data)->h_cmds;
	while (temp)
	{
		if (exec_builtin(temp, data))
			return (1);
		else
		{
			temp->pid = fork();
			if (temp->pid == 0)
			{
				if (check_cmd(temp))
					exec_error(temp);
				dup2(temp->to_read, STDIN_FILENO);
				dup2(temp->to_write, STDOUT_FILENO);
				dprintf(1, "Read: [%d] Write: [%d]\n", temp->to_read, temp->to_write);
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
	int		nb_process;
	int		pipefd[2];
	t_cmd	*cmd;

	nb_process = count_cmds(data) - 1;
	cmd = data->h_cmds;
	if (cmd->nb_infiles > 0)
		cmd->to_read = cmd->infiles[cmd->nb_infiles - 1];
	while (nb_process > 0)
	{
		if (pipe(pipefd) < 0)
			ft_error("Error initializing pipes\n", &data);
		cmd->to_write = pipefd[1];
		cmd->next->to_read = pipefd[0];
		nb_process--;
		// printf("Pipe: to_read [%d], to_write [%d]\n", cmd->to_read, cmd->to_write);
	}
	if (cmd->nb_outfiles > 0)
		cmd->to_write = cmd->outfiles[cmd->nb_outfiles - 1];
}

int	exec_cmds(t_data **data)
{
	init_pipes(*data);
	exec_now(data);
	return (0);
}
