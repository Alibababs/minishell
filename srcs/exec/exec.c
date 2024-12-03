/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:11:38 by phautena          #+#    #+#             */
/*   Updated: 2024/12/03 18:38:26 by pbailly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_all(t_cmd **h_cmd)
{
	t_cmd	*temp;
	int		status;

	status = 0;
	temp = *h_cmd;
	while (temp)
	{
		if (temp->pid > -1)
		{
			waitpid(temp->pid, &status, 0);
			g_exit_status = 1;
			return ;
		}
		if ((status) == 0)
			g_exit_status = 0;
		else
			g_exit_status = 1;
		temp = temp->next;
	}
}

static void	close_pipes(t_cmd **h_cmd)
{
	t_cmd	*temp;

	temp = *h_cmd;
	while (temp)
	{
		if (temp->to_read > -1)
			close(temp->to_read);
		temp->to_read = -1;
		if (temp->to_write > -1)
			close(temp->to_write);
		temp->to_write = -1;
		temp = temp->next;
	}
}

static int	init_pipes(t_cmd **h_cmd)
{
	int		nb_process;
	int		pipefd[2];
	t_cmd	*temp;

	nb_process = count_cmds(h_cmd) - 1;
	temp = *h_cmd;
	if (temp->infiles > 0)
		temp->to_read = temp->fd_in[temp->infiles - 1];
	while (nb_process > 0)
	{
		if (pipe(pipefd) < 0)
			return (1);
		temp->to_write = pipefd[1];
		if (temp->next)
			temp->next->to_read = pipefd[0];
		temp = temp->next;
		nb_process--;
	}
	if (temp->outfiles > 0)
		temp->to_write = temp->fd_out[temp->outfiles - 1];
	return (0);
}

static int	exec_cmds(t_cmd **h_cmd, char **envp, t_env **h_env)
{
	t_cmd	*temp;

	temp = *h_cmd;
	while (temp)
	{
		// dprintf(1, "CMD SIZE: %d\n", count_cmds(h_cmd));
		// dprintf(1, "WTF\n");
		if (!exec_is_builtin(temp->path) && !check_exec_cmds(h_cmd))
		{
			temp->pid = fork();
			if (temp->pid == 0)
			{
				if (dup2(temp->to_read, STDIN_FILENO) == -1)
					perror("dup2");
				if (dup2(temp->to_write, STDOUT_FILENO) == -1)
					perror("dup2");
				close_pipes(h_cmd);
				execve(temp->path, temp->argv, envp);
			}
			else if (temp->pid < 0)
				return (1);
		}
		else if (exec_is_builtin(temp->path) == 1)
			exec_builtin(temp, h_env);
		temp = temp->next;
	}
	close_pipes(h_cmd);
	wait_for_all(h_cmd);
	return (0);
}

int	exec(t_cmd **h_cmd, char **envp, t_env **h_env)
{
	if (init_pipes(h_cmd))
		return (printf("Failed to initialize pipes\n"));
	if ((*h_cmd)->to_read > -1)
		dup2((*h_cmd)->to_read, STDIN_FILENO);
	if (exec_cmds(h_cmd, envp, h_env))
		return (printf("An error occured while executing commands\n"));
	return (0);
}
