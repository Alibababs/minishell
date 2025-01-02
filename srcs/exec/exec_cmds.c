/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:18:46 by p0ulp1            #+#    #+#             */
/*   Updated: 2025/01/02 16:25:12 by p0ulp1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_pipes(t_data *data)
{
	int		nb_process;
	int		pipefd[2];
	t_cmd	*cmd;

	nb_process = count_cmds(data) - 1;
	cmd = data->h_cmds;
	if (cmd->nb_infiles > 0)
		cmd->to_read = cmd->infiles[cmd->nb_infiles - 1];
	// Need an else? If no infile, what value?
	while (nb_process > 0)
	{
		if (pipe(pipefd) < 0)
			ft_error("Error initializing pipes\n", &data);
		cmd->to_write = pipefd[1];
		if (nb_process > 1)
			cmd->next->to_read = pipefd[0];
		nb_process--;
		printf("Pipe created\n");
	}
	if (cmd->nb_outfiles > 0)
		cmd->to_write = cmd->outfiles[cmd->nb_outfiles - 1];
}

int	exec_cmds(t_data **data)
{
	init_pipes(*data);
	if (exec_builtin((*data)->h_cmds, data))
		return (1);
	return (0);
}
