/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:01:02 by pbailly           #+#    #+#             */
/*   Updated: 2024/12/03 17:37:44 by pbailly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_status = 0;

static void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_child_slash(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
}

static void	handle_child_c(int sig)
{
	(void)sig;
	printf("\n");
}

void	ft_signals(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, &handle_child_c);
		signal(SIGQUIT, &handle_child_slash);
	}
}
