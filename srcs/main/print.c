/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:26:33 by p0ulp1            #+#    #+#             */
/*   Updated: 2025/01/16 15:44:44 by phautena         ###   ########.fr       */
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
		dprintf(2, "\nPath: [%s]\n", temp->path);
		for (int i = 0; temp->argv[i]; i++)
			dprintf(2, "Argv [%d]: [%s]\n", i, temp->argv[i]);
		if (temp->infile > -1)
			dprintf(2, "infile: [%d] ", temp->infile);
		else
			dprintf(2, "to_read: [%d] ", temp->to_read);
		if (temp->outfile > -1)
			dprintf(2, "outfile: [%d]\n", temp->outfile);
		else
			dprintf(2, "to_write: [%d]\n", temp->to_write);
		// if (temp->here_doc == true)
			// dprintf(2, "Heredoc: %s\n", temp->hd_del->value);
		temp = temp->next;
	}
}
