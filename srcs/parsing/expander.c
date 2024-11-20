/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:56:15 by phautena          #+#    #+#             */
/*   Updated: 2024/11/20 17:31:29 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*triple_join(char *s1, char *s2, char *s3)
{
	char	*res;
	int		i;
	int		j;
	int		s1l;
	int		s2l;

	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	res = malloc(sizeof(char) * (s1l + s2l + ft_strlen(s3) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = -1;
	while (s1[++j])
		res[i++] = s1[j];
	j = -1;
	while (s2[++j])
		res[i++] = s2[j];
	j = -1;
	while (s3[++j])
		res[i++] = s3[j];
	res[i] = '\0';
	return (res);
}

static char	*extract_env_name(char *value)
{
	int		i;
	int		start;
	char	*res;

	i = 0;
	while (value[i] && value[i] != '$')
		i++;
	i++;
	start = i;
	while (value[i] && (ft_isalnum(value[i]) || ft_isalpha_upper(value[i])))
		i++;
	res = ft_substr(value, start, i - start);
	return (res);
}

static char	*get_new_value(t_token *current, char *value, char *name)
{
	char	*begin;
	char	*end;
	char	*res;
	int		i;

	(void)value;
	i = -1;
	while (current->value[++i] != '$')
		;
	begin = ft_substr(current->value, 0, i);
	if (!begin)
		return (NULL);
	i += ft_strlen(name) + 1;
	end = ft_substr(current->value, i, ft_strlen(current->value));
	if (!end)
		return (NULL);
	res = triple_join(begin, value, end);
	return (res);
}

static int	expand_node(t_token *current, t_env **h_env)
{
	char	*name;
	char	*value;
	char	*res;

	name = extract_env_name(current->value);
	if (!name)
		return (1);
	value = get_var(name, h_env);
	if (!value)
		return (2);
	res = get_new_value(current, value, name);
	if (!res)
		return (3);
	free(current->value);
	current->value = res;
	return (0);
}

void	expander(t_head *head)
{
	t_token	*temp;

	temp = head->h_token;
	while (temp)
	{
		if (temp->token != S_QUOTE && ft_strchr(temp->value, '$'))
			expand_node(temp, &head->h_env);
		temp = temp->next;
	}
}
