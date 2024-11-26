/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:05:20 by phautena          #+#    #+#             */
/*   Updated: 2024/11/21 11:12:03 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_head *head, char *str)
{
	printf("syntax error near unexpected token `%s'\n", str);
	free_token(&head->h_token);
	free_cmd(&head->h_cmd);
	return (1);
}
