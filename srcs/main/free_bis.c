/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:54:56 by phautena          #+#    #+#             */
/*   Updated: 2025/01/09 14:56:11 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_cmds(t_data **data)
{
	t_cmd *temp;
	t_cmd *next;

	temp = (*data)->h_cmds;
	while (temp)
	{
		next = temp->next;
		if (temp->path)
			free(temp->path);
		if (temp->argv)
			free_array(temp->argv);
		if (temp->infiles)
			free(temp->infiles);
		if (temp->outfiles)
			free(temp->outfiles);
		free(temp);
		temp = next;
	}
	(*data)->h_cmds = NULL;
}