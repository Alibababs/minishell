/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:24:36 by phautena          #+#    #+#             */
/*   Updated: 2024/11/06 12:26:59 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_end(char *to_tokenize, t_token **head)
{
	t_token	*new_token;
	t_token	*temp;

	if (*head == NULL)
		add_token_empty(to_tokenize, head);
	else
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return ;
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
		new_token->next = NULL;
		new_token->prev = temp;
		new_token->value = to_tokenize;
	}
}

void	add_token_empty(char *to_tokenize, t_token **head)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->value = to_tokenize;
	*head = new_token;
}

void	print_token(t_token **head)
{
	int		i;
	t_token	*temp;

	if (!*head)
		return ;
	i = 0;
	temp = *head;
	while (temp)
	{
		printf("TOKEN [%d]\n", i);
		printf("Value: %s\n", temp->value);
		printf("Token: %u\n", temp->token);
		printf("\n\n");
		temp = temp->next;
		i++;
	}
}

int	check_quotes_closed(char *input)
{
	int	i;
	int	squotes;
	int	dquotes;

	i = -1;
	squotes = 0;
	dquotes = 0;
	while (input[++i])
	{
		if (input[i] == 39)
			squotes++;
		else if (input[i] == 34)
			dquotes++;
	}
	if (squotes % 2 != 0 || dquotes % 2 != 0)
		return (1);
	return (0);
}
