/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:21:37 by ubuntu            #+#    #+#             */
/*   Updated: 2025/01/13 14:56:24 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_files(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_infiles)
	{
		if (cmd->infiles[i] < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->infiles_names[i], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
