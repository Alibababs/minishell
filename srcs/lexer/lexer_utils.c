/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:00:47 by phautena          #+#    #+#             */
/*   Updated: 2024/10/02 15:01:10 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	char	**builtin;
	int		i;

	builtin = declare_builtin();
	if (!builtin)
		return (ERROR);
	i = 0;
	while (builtin[i])
	{
		if (!ft_strcmp(str, builtin[i]))
			return (free_array(builtin), BUILTIN);
		i++;
	}
	free(builtin);
	return (ERROR);
}

char	**declare_builtin(void)
{
	char	**builtin;

	builtin = malloc(sizeof(char *) * 8);
	if (!builtin)
		return (NULL);
	builtin[0] = "echo";
	builtin[1] = "cd";
	builtin[2] = "pwd";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "env";
	builtin[6] = "exit";
	builtin[7] = NULL;
	return (builtin);
}
