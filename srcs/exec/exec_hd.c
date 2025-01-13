/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:32:41 by phautena          #+#    #+#             */
/*   Updated: 2025/01/13 14:13:04 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_write(char *lim, int fd_in)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(line, lim, ft_strlen(lim)))
		{
			free(line);
			return ;
		}
		ft_putstr_fd(line, fd_in);
		free(line);
	}
}

int	exec_hd(t_data **data)
{
	t_cmd	*temp;
	int		fd;

	temp = (*data)->h_cmds;
	fd = -1;
	while (temp)
	{
		if (temp->here_doc == true)
		{
			fd = open("temp.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd < 0)
				return (1);
			here_doc_write(temp->hd_del->value, fd);
			close(fd);
			fd = open("temp.txt", O_RDONLY);
			temp->infiles = &fd;
			temp->nb_infiles = 1;
			if (fd < 0)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	is_dir(t_cmd *cmd, t_data **data)
{
	struct stat	stats;

	if (stat(cmd->path, &stats) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_status = 127;
		free_data(data);
		exit(127);
	}
	if (S_ISDIR(stats.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->path, 2);
		ft_putstr_fd(" : Is a directory\n", 2);
		g_exit_status = 126;
		free_data(data);
		exit(126);
	}
}

int	check_cmd(t_cmd *cmd, t_data **data)
{
	struct stat	stats;

	stat(cmd->path, &stats);
	if (cmd->path && ft_strchr(cmd->path, '/'))
		is_dir(cmd, data);
	if (cmd->path && access(cmd->path, X_OK) != 0 && ft_strstr(cmd->path, "./"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_exit_status = 126;
		exit(126);
	}
	if (!cmd->path || access(cmd->path,
			X_OK) != 0 || S_ISDIR(stats.st_mode))
		return (1);
	else if (cmd->to_read < 0 || cmd->to_write < 0)
	{
		cmd->no_cmd = true;
		return (1);
	}
	return (0);
}

void	exec_error(t_cmd *cmd, t_data **data)
{
	if (cmd->no_cmd == false)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_exit_status = 127;
		free_data(data);
		exit(127);
	}
	else
	{
		g_exit_status = 1;
		free_data(data);
		exit(1);
	}
}
