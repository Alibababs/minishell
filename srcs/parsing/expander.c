/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:56:15 by phautena          #+#    #+#             */
/*   Updated: 2024/11/11 15:19:04 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *expand_assemble(char *first, char *second, char *value)
{
	char	*begin;
	char	*res;

	if (!first || !second || !value)
		return (NULL);
	begin = ft_strjoin(first, value);
	if (!begin)
		return (NULL);
	res = ft_strjoin(begin, second);
	if (!res)
		return (free(begin), NULL);
	free(begin);
	return (res);
}

static char	*expand_value(char *old, char *name, char *value)
{
	char	*first;
	char	*second;
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (old[i] != '$')
		i++;
	first = ft_substr(old, 0, i);
	if (!first)
		return (NULL);
	i += ft_strlen(name) + 1;
	j = i;
	second = ft_substr(old, j, ft_strlen(old));
	if (!second)
		return (NULL);
	res = expand_assemble(first, second, value);
	if (!res)
		return (NULL);
	return (res);
}

static char *extract_var_name(char *value)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	while (value[++i] && value[i] != '$')
		;
	j = i;
	while (value[i])
	{
		if (ft_isspace(value[i]))
			break ;
		i++;
	}
	res = ft_substr(value, j + 1, i - j - 1);
	if (!res)
		return (NULL);
	return (res);
}

static void	expand_node(t_token *current, t_env **h_env)
{
	char	*name;
	char	*value;
	char	*final;

	name = extract_var_name(current->value);
	if (!name)
		return ;
	value = get_var(name, h_env);
	if (!value)
		return ;
	final = expand_value(current->value, name, value);
	free(current->value);
	current->value = final;
}

void	expander(t_token **h_token, t_env **h_env)
{
	t_token	*temp;

	temp = *h_token;
	while (temp)
	{
		if (temp->token != S_QUOTE && ft_strchr(temp->value, '$'))
			expand_node(temp, h_env);
		temp = temp->next;
	}
}
