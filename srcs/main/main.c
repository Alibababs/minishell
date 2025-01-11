/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:36:49 by p0ulp1            #+#    #+#             */
/*   Updated: 2025/01/11 17:05:34 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup(t_data **data)
{
	free_tokens(data);
	free_cmds(data);
}

static void	process_command(t_data **data, char *input)
{
	if (lexer(*data, input))
		return ;
	// print_tokens((*data)->h_tokens);
	if (expander(*data))
		return ;
	if (parsing(*data))
		return ;
	if (exec(data))
		return ;
	// print_env(data);
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
	(*data)->envp = envp;
	(*data)->str = NULL;
	init_env(data, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	char	*input;

	data = NULL;
	init_data(&data, envp);
	while (argc && argv)
	{
		ft_signals(1);
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
			cleanup(&data);
		}
	}
	free_data(&data);
}
