/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:31:01 by pbailly           #+#    #+#             */
/*   Updated: 2024/10/02 15:45:09 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(void)
{
	ft_signals();
}

int	main(void)
{
	t_input	input;

	init_data();
	while (1)
	{
		input.input = readline("minishelldefou> ");
		if (!input.input)
		{
			printf("exit\n");
			break ;
		}
		if (input.input)
			add_history(input.input);
		if (lexer(&input) == ERROR)
			ft_printf("Error while lexing\n");
		free_input_struct(&input);
	}
	return (0);
}
