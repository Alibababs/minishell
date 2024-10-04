/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:12:35 by phautena          #+#    #+#             */
/*   Updated: 2024/10/04 13:22:00 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_var(char **envp)
{
	t_env	*head;

	head = NULL;
	init_env(&head, envp);
	// print_env(&head);
	// print_export(&head);
	export_var("TEST=This is a test!", &head);
	printf("Value: %s\n", get_var("TEST", &head));
	free_env(&head);
}

void	export_var(char *var, t_env **head)
{
	char	*name;
	char	*value;

	if (!var)
		return ;
	name = get_env_name(var);
	if (!name)
		return ;
	value = get_env_value(var);
	if (!value)
		return (free(name));
	add_env_end(name, value, head);
}

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
