/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:02:05 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/11/30 12:28:00 by p0ulp1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_data *data, char *msg)
{
	printf("An error occured:\n");
	printf("%s\n", msg);
	(void)data;
}

void	mem_error(t_data *data)
{
	printf("A memory allocation has failed.\n");
	printf("Please provide more memory to the process.\nExiting\n");
	exit(1);
	(void)data;
}
