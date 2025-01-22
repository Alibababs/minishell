/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:53:46 by p0ulp1            #+#    #+#             */
/*   Updated: 2025/01/22 12:50:20 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_status = 0;

static void	handle_sigint(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_child_slash(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 2);
}

static void	handle_child_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

static void	handle_heredoc(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	rl_done = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "");
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
	else if (mode == 3)
	{
		signal(SIGINT, &handle_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
