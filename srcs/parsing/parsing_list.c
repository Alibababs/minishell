/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:36:43 by phautena          #+#    #+#             */
/*   Updated: 2024/11/11 16:04:52 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		init_cmd_node(temp);
	}
}
