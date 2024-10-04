/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:35:49 by phautena          #+#    #+#             */
/*   Updated: 2024/10/04 11:13:35 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(char *input)
{
	t_token	*head;

	head = NULL;
	lex_all(input, &head);
	fix_redir_list(&head);
	tokenize(&head);
	print_token(&head);
	free_token(&head);
	return (0);
}

void	lex_all(char *input, t_token **head)
{
	int		i;
	int		*i_ptr;

	*head = NULL;
	i = 0;
	i_ptr = &i;
	while (input[i])
	{
		if (input[i] == '$')
			tokenize_env(i_ptr, input, head);
		else if (input[i] == 34)
			tokenize_quote(i_ptr, input, head, 1);
		else if (input[i] == 39)
			tokenize_quote(i_ptr, input, head, 2);
		else if (is_sep(input[*i_ptr]))
			tokenize_char(i_ptr, input, head);
		else
			tokenize_str(i_ptr, input, head);
	}
}

void	tokenize_env(int *i_ptr, char *input, t_token **head)
{
	int		start;
	char	*to_tokenize;

	start = *i_ptr;
	*i_ptr += 1;
	while (input[*i_ptr] && !is_sep(input[*i_ptr]))
		*i_ptr += 1;
	to_tokenize = ft_substr(input, start, *i_ptr - start);
	if (!to_tokenize)
		return ;
	add_token_end(to_tokenize, head);
}

void	tokenize_quote(int *i_ptr, char *input, t_token **head, int mode)
{
	char	*to_tokenize;
	int		quote;
	int		start;

	if (mode == 1)
		quote = 34;
	else
		quote = 39;
	start = *i_ptr;
	*i_ptr += 1;
	while (input[*i_ptr] && input[*i_ptr] != quote)
		*i_ptr += 1;
	to_tokenize = ft_substr(input, start, *i_ptr - start + 1);
	*i_ptr += 1;
	if (!to_tokenize)
		return ;
	add_token_end(to_tokenize, head);
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


