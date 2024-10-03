/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_is_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:37:35 by phautena          #+#    #+#             */
/*   Updated: 2024/10/03 14:47:37 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in(char *str)
{
	if (!ft_strncmp(str, "<", 2))
		return (0);
	return (1);
}

int	is_out(char *str)
{
	if (!ft_strncmp(str, ">", 2))
		return (0);
	return (1);
}

int	is_append(char *str)
{
	if (!ft_strncmp(str, ">>", 3))
		return (0);
	return (1);
}

int	is_hd(char *str)
{
	if (!ft_strncmp(str, "<<", 3))
		return (0);
	return (1);
}

int	is_pipe(char *str)
{
	if (!ft_strncmp(str, "|", 2))
		return (0);
	return (1);
}
