/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:31:01 by pbailly           #+#    #+#             */
/*   Updated: 2024/10/04 13:00:08 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(void)
{
	ft_signals();
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*head_env;

	init_data();
	///ENV TEST///
	head_env = NULL;
	init_env(&head_env, envp);
	print_export(&head_env);
	////////////////////
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
			lexer(input);
			add_history(input);
		}
	}
	(void)envp;
	return (0);
}
