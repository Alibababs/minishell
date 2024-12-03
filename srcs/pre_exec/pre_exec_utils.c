/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:51:57 by phautena          #+#    #+#             */
/*   Updated: 2024/12/03 13:19:04 by pbailly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exec_cmds(t_cmd **h_cmd)
{
	t_cmd	*temp;

	temp = *h_cmd;
	while (temp)
	{
		if (access(temp->path, X_OK) != 0)
			return (printf("minishelldefou: %s command not found\n",
					temp->path));
		temp = temp->next;
	}
	return (0);
}
