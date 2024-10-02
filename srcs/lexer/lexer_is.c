/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:59:45 by phautena          #+#    #+#             */
/*   Updated: 2024/10/02 15:00:06 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_argv(int prev)
{
	if (prev == CMD || prev == BUILTIN)
		return (ARGV);
	return (ERROR);
}

int	is_file(int prev)
{
	if (prev == REDIR_IN || prev == REDIR_OUT)
		return (FILE);
	return (ERROR);
}

int	is_env(char *str)
{
	if (str[0] == '$')
		return (ENVAR);
	return (ERROR);
}

int	is_pipe(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	return (ERROR);
}

int	is_redirection(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (REDIR_OUT);
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
		return (REDIR_IN);
	return (ERROR);
}
