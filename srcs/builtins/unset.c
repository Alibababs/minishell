/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:01:19 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/19 12:41:16 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_destroy(t_data *data, t_env *temp)
{
	if (temp == data->h_env)
		data->h_env = temp->next;
	if (temp->prev)
		temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	free(temp->name);
	free(temp->value);
	free(temp);
}

void	ft_unset(char **argv, t_data **data)
{
	int		i;
	t_env	*temp;

	i = 1;
	while (argv[i])
	{
		temp = (*data)->h_env;
		while (temp)
		{
			if (!ft_strcmp(argv[i], temp->name))
			{
				unset_destroy(*data, temp);
				break ;
			}
			temp = temp->next;
		}
		i++;
	}
}
