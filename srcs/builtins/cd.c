/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:58:26 by phautena          #+#    #+#             */
/*   Updated: 2024/11/12 12:06:15 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *directory)
{
	int	ret;

	ret = chdir(directory);
	if (ret != 0)
		perror("Can't open directory\n");
}
