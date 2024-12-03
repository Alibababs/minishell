/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:52:46 by phautena          #+#    #+#             */
/*   Updated: 2024/12/03 14:02:34 by pbailly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n(char *str)
{
	int	i;

	i = 1;
	if (!str || str[0] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	if (i > 1)
		return (0);
	return (1);
}

static int	echo_print(char *argv[])
{
	int	i;

	i = 1;
	if (!is_n(argv[1]))
		i++;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (is_n(argv[1]))
		printf("\n");
	return (0);
}

void	ft_echo(char *argv[])
{
	echo_print(argv);
}
