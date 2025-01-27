/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:02:05 by p0ulp1            #+#    #+#             */
/*   Updated: 2025/01/27 10:21:59 by ubuntu           ###   ########.fr       */
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
	t_cmd	*temp;
	t_cmd	*next;

	temp = (*data)->h_cmds;
	while (temp)
	{
		next = temp->next;
		if (temp->path)
			free(temp->path);
		if (temp->argv)
			free_array(temp->argv);
		if (access("temp.txt", F_OK) && temp->infile > -1)
			close(temp->infile);
		if (temp->to_write > -1 && temp->outfile > -1)
			close(temp->outfile);
		free(temp);
		temp = next;
	}
	(*data)->h_cmds = NULL;
}

void	free_env(t_data **data)
{
	t_env	*temp;
	t_env	*next;

	temp = (*data)->h_env;
	while (temp)
	{
		next = temp->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		temp = next;
	}
	(*data)->h_env = NULL;
}

void	free_tokens(t_data **data)
{
	t_token	*temp;
	t_token	*next;

	if (!data || !(*data)->h_tokens)
		return ;
	temp = (*data)->h_tokens;
	while (temp)
	{
		next = temp->next;
		if (temp->value)
			free(temp->value);
		free(temp);
		temp = next;
	}
	(*data)->h_tokens = NULL;
}

void	free_data(t_data **data)
{
	if (!data || !*data)
		return ;
	close_pipes(data);
	if ((*data)->h_tokens)
		free_tokens(data);
	if ((*data)->h_env)
		free_env(data);
	if ((*data)->h_cmds)
		free_cmds(data);
	if (!access("temp.txt", F_OK))
		unlink("temp.txt");
	free(*data);
	*data = NULL;
}
