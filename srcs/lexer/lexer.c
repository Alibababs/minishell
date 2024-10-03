/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:35:49 by phautena          #+#    #+#             */
/*   Updated: 2024/10/03 12:30:58 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(char *input)
{
	t_token	*head;

	head = NULL;
	tokenize_all(input, &head);
	fix_redir_list(&head);
	print_token(&head);
	return (0);
}

void	tokenize_all(char *input, t_token **head)
{
	int		i;
	int		*i_ptr;

	*head = NULL;
	i = 0;
	i_ptr = &i;
	while (input[i])
	{
		if (is_sep(input[*i_ptr]))
			tokenize_char(i_ptr, input, head);
		else
			tokenize_str(i_ptr, input, head);
	}
}

void	tokenize_char(int *i_ptr, char *input, t_token **head)
{
	char	*to_tokenize;

	to_tokenize = malloc(sizeof(char *));
	if (!to_tokenize)
		return ;
	to_tokenize[0] = input[*i_ptr];
	to_tokenize[1] = '\0';
	add_token_end(to_tokenize, head);
	*i_ptr += 1;
}

void	tokenize_str(int *i_ptr, char *input, t_token **head)
{
	char	*to_tokenize;
	int		i;

	to_tokenize = malloc(sizeof(char *));
	if (!to_tokenize)
		return ;
	i = 0;
	while (input[*i_ptr] && !is_sep(input[*i_ptr]))
	{
		to_tokenize[i] = input[*i_ptr];
		i++;
		*i_ptr += 1;
	}
	to_tokenize[i] = '\0';
	add_token_end(to_tokenize, head);
}

int	is_sep(char c)
{
	if (c == '|' || c == ' ' || c == '<' || c == '>')
		return (1);
	return (0);
}
