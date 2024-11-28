/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:45:57 by phautena          #+#    #+#             */
/*   Updated: 2024/11/28 15:14:03 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cmd(t_head *head)
{
	printf("Error occured while allocating memory for cmd nodes\nExiting\n");
	free_token(&head->h_token);
	free_cmd(&head->h_cmd);
	exit(1);
}

void	cmd_cleanup(t_head *head)
{
	free_token(&head->h_token);
	free_cmd(&head->h_cmd);
}

void	close_fds(t_cmd *current)
{
	int	i;

	if (current->infiles > 0)
	{
		i = current->infiles;
		while (i > 0)
		{
			if (current->fd_in[i] > 0)
				close(current->fd_in[i]);
			i--;
		}
	}
	if (current->outfiles > 0)
	{
		i = current->outfiles;
		while (i > 0)
		{
			if (current->fd_out[i] > 0)
				close(current->fd_out[i]);
			i--;
		}
	}
}
