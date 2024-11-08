/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:35:49 by phautena          #+#    #+#             */
/*   Updated: 2024/11/08 11:45:03 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tokenize_quote(int *i_ptr, char *input, t_token **head, int mode)
{
	char	*to_tokenize;
	int		quote;
	int		start;

	if (mode == 1)
		quote = 34;
	else
		quote = 39;
	if (input[*i_ptr + 1] != '\0')
	{
		if (input[*i_ptr + 1] == quote)
		{
			*i_ptr += 2;
			return ;
		}
	}
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

static void	tokenize_char(int *i_ptr, char *input, t_token **head)
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

static void	tokenize_str(int *i_ptr, char *input, t_token **head)
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

static void	lex_all(char *input, t_token **head)
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

int	lexer(char *input)
{
	t_token	*head;

	if (ft_strlen(input) == 0)
		return (1);
	head = NULL;
	if (check_quotes_closed(input))
		return (ft_printf("A quote is not closed. Please fix your quotes.\n"));
	lex_all(input, &head);
	tokenize(&head);
	lexer_fix_master(&head);
	print_token(&head);
	fix_redir_list(&head);
	free_token(&head);
	return (0);
}
