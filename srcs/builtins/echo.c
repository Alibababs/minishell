/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:52:46 by phautena          #+#    #+#             */
/*   Updated: 2024/11/27 16:18:31 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_write(char *argv[], int newline_flag)
{
	int		i;

	if (newline_flag == 1)
		i = 1;
	else
		i = 0;
	while (argv[++i])
		printf("%s", argv[i]);
	if (newline_flag == 0)
		printf("\n");
}

void	echo(char *argv[])
{
	if (!ft_strncmp(argv[1], "-n", 3))
		echo_write(argv, 1);
	else
		echo_write(argv, 0);
}
