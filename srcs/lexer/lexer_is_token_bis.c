/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_is_token_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:00:07 by phautena          #+#    #+#             */
/*   Updated: 2024/11/20 11:22:46 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**declare_builtin(void)
{
	char	**builtin;

	builtin = malloc(sizeof(char *) * 8);
	if (!builtin)
		return (NULL);
	builtin[0] = "echo";
	builtin[1] = "cd";
	builtin[2] = "pwd";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "env";
	builtin[6] = "exit";
	builtin[7] = NULL;
	return (builtin);
}

int	is_argv(t_type prev)
{
	if (prev == CMD || prev == BUILTIN || prev == ARGV || prev == HEREDOC
		|| prev == S_QUOTE || prev == D_QUOTE)
		return (0);
	return (1);
}

int	is_squote(char *str)
{
	int	len;
	int	quote;

	len = ft_strlen(str) - 1;
	quote = 39;
	if (str[0] == quote && str[len] == quote)
		return (0);
	return (1);
}

int	is_dquote(char *str)
{
	int	len;
	int	quote;

	len = ft_strlen(str) - 1;
	quote = 34;
	if (str[0] == quote && str[len] == quote)
		return (0);
	return (1);
}

int	is_builtin_bis(char *str, t_token **h_token)
{
	char	**builtin;
	int		i;

	builtin = declare_builtin();
	if (!builtin)
		return ((error_token(h_token)), 1);
	i = 0;
	while (builtin[i])
	{
		if (!ft_strncmp(str, builtin[i], ft_strlen(str)))
			return (free(builtin), 1);
		i++;
	}
	free(builtin);
	return (0);
}
