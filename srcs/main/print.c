/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:26:33 by p0ulp1            #+#    #+#             */
/*   Updated: 2025/01/07 13:32:48 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_data **data)
{
	t_env	*temp;

	if (!(*data)->h_env)
		return ;
	temp = (*data)->h_env;
	while (temp)
	{
		if (temp->value)
			printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

void	print_tokens(t_token *temp)
{
	while (temp)
	{
		printf("Value: [%s], Token: [%d]\n", temp->value, temp->token);
		temp = temp->next;
	}
}

void	print_cmds(t_cmd *temp)
{
	while (temp)
	{
		printf("\nPath: [%s]\n", temp->path);
		for (int i = 0; temp->argv[i]; i++)
			printf("Argv [%d]: [%s]\n", i, temp->argv[i]);
		printf("Infiles: %d\n", temp->nb_infiles);
		printf("Outfiles: %d\n", temp->nb_outfiles);
		if (temp->here_doc == true)
			printf("Heredoc: %s\n", temp->hd_del->value);
		temp = temp->next;
	}
}
