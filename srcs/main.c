/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:31:01 by pbailly           #+#    #+#             */
/*   Updated: 2024/11/19 13:22:37 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_command(char *input, t_env **h_env)
{
	t_token	*h_token;
	t_cmd	*h_cmd;


	h_token = NULL;
	h_cmd = NULL;
	if (ft_strlen(input) == 0)
		return ;
	lexer(input, &h_token);
	expander(&h_token, h_env);
	parsing(&h_token, &h_cmd);
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
	env_var(envp, &h_env);
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
