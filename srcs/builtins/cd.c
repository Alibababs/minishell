/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:02:01 by pbailly           #+#    #+#             */
/*   Updated: 2024/12/19 23:02:05 by pbailly          ###   ########.fr       */
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
