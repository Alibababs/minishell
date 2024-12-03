/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_is_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:37:35 by phautena          #+#    #+#             */
/*   Updated: 2024/12/03 13:14:22 by pbailly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (0);
	return (1);
}

int	is_out(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (0);
	return (1);
}

int	is_append(char *str)
{
	if (!ft_strcmp(str, ">>"))
		return (0);
	return (1);
}

int	is_hd(char *str)
{
	if (!ft_strcmp(str, "<<"))
		return (0);
	return (1);
}

int	is_pipe(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (0);
	return (1);
}
