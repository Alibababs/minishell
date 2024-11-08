/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:56:15 by phautena          #+#    #+#             */
/*   Updated: 2024/11/08 14:35:57 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *extract_var_name(char *value)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	while (value[++i] && value[i] != '$')
		;
	j = i;
	while (value[++i])
	{
		if (ft_isspace(value[i]))
			break ;
	}
	res = ft_substr(value, j, i - 1);
	if (!res)
		return (NULL);
	return (res);
}

static void	expand_node(t_token *current, t_env **h_env)
{
	char	*name;
	char	*value;

	name = extract_var_name(current->value);
	if (!name)
		return ;
	value = get_var(name, h_env);
	if (!value)
		return ;

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
