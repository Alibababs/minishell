/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:45:57 by phautena          #+#    #+#             */
/*   Updated: 2024/11/20 12:22:57 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cmd(t_head *head)
{
	printf("Error occured while allocating memory for cmd nodes\nExiting\n");
	free_token(&head->h_token);
	free_cmd(&head->h_cmd);
	exit(1);
}

void	cmd_cleanup(t_head *head)
{
	free_token(&head->h_token);
	free_cmd(&head->h_cmd);
}
