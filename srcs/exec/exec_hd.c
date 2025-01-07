/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:32:41 by phautena          #+#    #+#             */
/*   Updated: 2025/01/07 14:42:01 by phautena         ###   ########.fr       */
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

int	check_cmd(t_cmd *cmd)
{
	if (!cmd->path)
		return (1);
	if (access(cmd->path, X_OK) != 0)
		return (2);
	if (cmd->to_read < 0)
		return (3);
	if (cmd->to_write < 0)
		return (4);
	return (0);
}

void	exec_error(t_cmd *cmd)
{
	if (cmd->no_cmd == false)
		printf("%s: command not found\n", cmd->argv[0]);
	exit(1);
}
