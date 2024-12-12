/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:36:49 by p0ulp1            #+#    #+#             */
/*   Updated: 2024/12/12 13:13:20 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_command(t_data **data, char *input)
{
	if (lexer(*data, input))
		return ;
	expander(*data);
	if (parsing(*data))
		return ;
	print_tokens((*data)->h_tokens);
	if (exec(*data))
		return ;
	print_cmds((*data)->h_cmds);
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
