/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:12:35 by phautena          #+#    #+#             */
/*   Updated: 2024/10/04 15:40:46 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_var(char **envp)
{
	t_env	*head;

	head = NULL;
	init_env(&head, envp);
	// export_var("EFD", &head);
	// print_env(&head);
	// print_export(&head);
	// printf("Value: %s\n", get_var("TEST", &head));
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
	if (!ft_strchr(var, '='))
	{
		add_env_end(name, NULL, head);
		return ;
	}
	value = get_env_value(var);
	if (!value)
		value = NULL;
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
		if (temp->value)
			printf("export %s=\"%s\"\n", temp->name, temp->value);
		else
			printf("export %s\n", temp->name);
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
		if (temp->value)
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
