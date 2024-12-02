/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:36:43 by phautena          #+#    #+#             */
/*   Updated: 2024/12/02 12:27:22 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_cmd **h_cmd)
{
	int		i;
	int		j;
	t_cmd	*temp;

	if (!*h_cmd)
		return ;
	i = 0;
	temp = *h_cmd;
	while (temp)
	{
		j = 0;
		printf("CMD [%d]\n", i);
		printf("Path: %s\n", temp->path);
		while (temp->argv[j])
		{
			printf("Argv [%d]: %s\n", j, temp->argv[j]);
			j++;
		}
		for (int k = 0; k < temp->infiles; k++)
			printf("In [%d]: %d\n", k, temp->fd_in[k]);
		printf("Infiles: %d\n", temp->infiles);
		for (int l = 0; l < temp->outfiles; l++)
			printf("Out [%d]: %d\n", l, temp->fd_out[l]);
		printf("Outfiles: %d\n", temp->outfiles);
		printf("PID: %d\n", temp->pid);
		printf("\n\n");
		temp = temp->next;
		i++;
	}
}

static void	init_cmd_node(t_cmd *current)
{
	current->path = NULL;
	current->argv = NULL;
	current->fd_in = NULL;
	current->fd_out = NULL;
	current->infiles = 0;
	current->outfiles = 0;
	current->to_read = -1;
	current->to_write = -1;
	current->pid = -1;
}

static int	add_cmd_empty(t_cmd **h_cmd)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (1);
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	init_cmd_node(new_cmd);
	*h_cmd = new_cmd;
	return (0);
}

int	add_cmd_end(t_cmd **h_cmd)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;

	if (*h_cmd == NULL)
	{
		if (add_cmd_empty(h_cmd) != 0)
			return (1);
	}
	else
	{
		new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
			return (1);
		temp = *h_cmd;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cmd;
		new_cmd->next = NULL;
		new_cmd->prev = temp;
		init_cmd_node(new_cmd);
	}
	return (0);
}

int	count_cmds(t_cmd **h_cmd)
{
	t_cmd	*temp;
	int		res;

	temp = *h_cmd;
	res = 0;
	while (temp)
	{
		res++;
		temp = temp->next;
	}
	return (res);
}
