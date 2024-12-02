/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:58:26 by phautena          #+#    #+#             */
/*   Updated: 2024/12/02 12:28:17 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	double_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	ft_cd(char **argv)
{
	int	ret;
	int	len;

	len = double_array_len(argv);
	if (len > 2)
	{
		printf("cd: too many arguments\n");
		return ;
	}
	ret = chdir(argv[1]);
	if (ret != 0)
		perror(argv[1]);
	// Changer Variable Environnement OLDPWD and PWD
}
