/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ulp1 <p0ulp1@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:36:49 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/11/30 12:48:35 by p0ulp1           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_data *data, char *envp[])
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (mem_error(data));
	data->h_env = NULL;
	data->h_tokens = NULL;
	data->h_cmds = NULL;
	init_env(data, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	data = NULL;
	init_data(data, envp);
	print_env(data);
	(void)argc;
	(void)argv;
}
