/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:31:01 by pbailly           #+#    #+#             */
/*   Updated: 2024/12/02 11:01:34 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_command(char *input, t_head *head, char **envp)
{
	head->h_token = NULL;
	head->h_cmd = NULL;
	if (ft_strlen(input) == 0)
		return ;
	if (lexer(input, &head->h_token))
		return ;
	expander(head);
	// print_token(&head->h_token);
	if (parsing(head))
		return ;
	if (pre_exec(&head->h_token, &head->h_cmd, head))
		return ;
	print_cmd(&head->h_cmd);
	if (exec(&head->h_cmd, envp, &head->h_env))
		return ;
	cmd_cleanup(head);
}

int	main(int argc, char **argv, char **envp)
{
	t_head	head;
	char	*input;

	env_var(envp, &head);
	while (argc && argv)
	{
		ft_signals(1);
		input = readline("minishelldefou> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input)
		{
			ft_signals(2);
			process_command(input, &head, envp);
			add_history(input);
		}
	}
	free_env(&head.h_env);
	return (0);
}
