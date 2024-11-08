/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:31:01 by pbailly           #+#    #+#             */
/*   Updated: 2024/11/08 14:34:57 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_command(char *input, t_env **h_env)
{
	t_token	*h_token;

	lexer(input, &h_token, h_env);
	expander(&h_token, h_env);
}

void	init_data(void)
{
	ft_signals();
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*h_env;
	char	*input;

	init_data();
	env_var(envp);
	while (argc && argv)
	{
		input = readline("minishelldefou> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input)
		{
			process_command(input, &h_env);
			add_history(input);
		}
	}
	(void)envp;
	return (0);
}
