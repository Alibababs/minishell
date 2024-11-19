/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:36:43 by phautena          #+#    #+#             */
/*   Updated: 2024/11/19 16:56:36 by phautena         ###   ########.fr       */
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
		printf("In: %d\n", temp->in);
		printf("Out: %d\n", temp->out);
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
	current->in = -1;
	current->out = -1;
	current->pid = -1;
}

static void	add_cmd_empty(t_cmd **h_cmd)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return ;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	init_cmd_node(new_cmd);
	*h_cmd = new_cmd;
}

void	add_cmd_end(t_cmd **h_cmd)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;

	if (*h_cmd == NULL)
		add_cmd_empty(h_cmd);
	else
	{
		new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
			return ;
		temp = *h_cmd;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cmd;
		new_cmd->next = NULL;
		new_cmd->prev = temp;
		init_cmd_node(new_cmd);
	}
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
