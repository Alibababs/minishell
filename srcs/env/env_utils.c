/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:12:35 by phautena          #+#    #+#             */
/*   Updated: 2024/10/04 13:00:20 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env **head)
{
	t_env	*temp;

	if (*head == NULL)
		return ;
	temp = *head;
	while (temp)
	{
		printf("export %s=\"%s\"\n", temp->name, temp->value);
		temp = temp->next;
	}
}

void	print_env(t_env **head)
{
	t_env	*temp;

	if (*head == NULL)
		return ;
	temp = *head;
	while (temp)
	{
		printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

char	*get_var(char *name, t_env **head)
{
	int	len;
	t_env	*temp;

	if (!name || *head == NULL)
		return (NULL);
	len = ft_strlen(name);
	temp = *head;
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, len))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
