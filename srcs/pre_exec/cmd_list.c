/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:36:43 by phautena          #+#    #+#             */
/*   Updated: 2024/11/26 15:13:05 by phautena         ###   ########.fr       */
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
		for (int h = 0; h < 2; h++)
			printf("In: %d\n", temp->in[h]);
		// printf("Out: %d\n", temp->out);
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
	current->in = NULL;
	current->out = NULL;
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
