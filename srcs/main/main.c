/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:36:49 by p0ulp1            #+#    #+#             */
/*   Updated: 2025/01/27 10:18:33 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup(t_data **data)
{
	free_tokens(data);
	free_cmds(data);
	if (!access("temp.txt", F_OK))
		unlink("temp.txt");
}

static int	process_command(t_data **data, char *input)
{
	if (lexer(data, input))
		return (1);
	// print_tokens((*data)->h_tokens);
	if (expander(data))
		return (1);
	if (parsing(data))
		return (1);
	exec(data);
	return (0);
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
	shlvl(data);
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
		else if (*input)
		{
			ft_signals(2);
			add_history(input);
			process_command(&data, input);
			cleanup(&data);
		}
	}
	free_data(&data);
}
