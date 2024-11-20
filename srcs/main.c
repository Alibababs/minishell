/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:31:01 by pbailly           #+#    #+#             */
/*   Updated: 2024/11/20 17:09:36 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_command(char *input, t_head *head)
{
	head->h_token = NULL;
	head->h_cmd = NULL;
	if (ft_strlen(input) == 0)
		return ;
	lexer(input, &head->h_token);
	expander(head);
	//Need to re-do expander (it was FREAKING SHIT)
	//Make PARSING ERRORS (Most important)
	parsing(&head->h_token, &head->h_cmd, head);
	cmd_cleanup(head);
}

void	init_data(void)
{
	ft_signals();
}

int	main(int argc, char **argv, char **envp)
{
	t_head	head;
	char	*input;

	init_data();
	env_var(envp, &head);
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
			process_command(input, &head);
			add_history(input);
		}
	}
	(void)envp;
	free_env(&head.h_env);
	return (0);
}
