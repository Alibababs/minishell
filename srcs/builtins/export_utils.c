/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:56:00 by alibabab          #+#    #+#             */
/*   Updated: 2025/01/15 20:56:38 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	msg_invalid_export(char *str)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

char	*ft_getenv(char *name, t_data **data)
{
	t_env	*temp;

	if (!name || !data)
		return (NULL);
	temp = (*data)->h_env;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
