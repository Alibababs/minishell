/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:36:49 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/08 16:10:51 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_command(t_data **data, char *input)
{
	lexer(&(*data)->h_tokens, input);
	return ;
}

static void	init_data(t_data **data, char *envp[])
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (mem_error(data));
	(*data)->h_env = NULL;
	(*data)->h_tokens = NULL;
	(*data)->h_cmds = NULL;
	init_env(data, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	char	*input;

	data = NULL;
	while (argc && argv)
	{
		ft_signals(1);
		init_data(&data, envp);
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		else if (input)
		{
			ft_signals(2);
			add_history(input);
			process_command(&data, input);
		}
	}
	free_data(&data);
}
