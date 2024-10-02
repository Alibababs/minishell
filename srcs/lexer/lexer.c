/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:17:58 by phautena          #+#    #+#             */
/*   Updated: 2024/10/02 15:01:05 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(t_input *input)
{
	char	**splitted;
	int		*tokenized;

	splitted = ft_split(input->input, ' ');
	if (!splitted)
		return (ERROR);
	tokenized = tokenize(splitted);
	if (!tokenized)
		return (free_array(splitted), ERROR);
	input->tokenized = tokenized;
	free_array(splitted);
	return (0);
}

int	*tokenize(char **splitted)
{
	int		i;
	int		*tokenized;

	tokenized = malloc(sizeof(int) * tab_len(splitted));
	if (!tokenized)
		return (NULL);
	i = 0;
	while (splitted[i])
	{
		if (i == 0)
			tokenized[i] = assign_first_token(splitted[i]);
		else
			tokenized[i] = assign_token(splitted[i], tokenized[i - 1]);
		i++;
	}
	return (tokenized);
}

int	assign_first_token(char *str)
{
	if (is_builtin(str) == BUILTIN)
		return (BUILTIN);
	else if (is_redirection(str) == REDIR_IN)
		return (REDIR_IN);
	else if (is_redirection(str) == REDIR_OUT)
		return (REDIR_OUT);
	else if (is_pipe(str) == PIPE)
		return (PIPE);
	else if (is_env(str) == ENVAR)
		return (ENVAR);
	else
		return (CMD);
}

int	assign_token(char *str, int prev)
{
	if (is_builtin(str) == BUILTIN)
		return (BUILTIN);
	else if (is_redirection(str) == REDIR_IN)
		return (REDIR_IN);
	else if (is_redirection(str) == REDIR_OUT)
		return (REDIR_OUT);
	else if (is_pipe(str) == PIPE)
		return (PIPE);
	else if (is_env(str) == ENVAR)
		return (ENVAR);
	else if (is_file(prev) == FILE)
		return (FILE);
	else if (is_argv(prev) == ARGV)
		return (ARGV);
	return (CMD);
}

