/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:11:44 by phautena          #+#    #+#             */
/*   Updated: 2024/08/01 12:39:45 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	len_s;

	len_s = gnl_strlen(s);
	if (s == NULL)
		return (NULL);
	if (start >= len_s)
		return (gnl_strdup(""));
	if (len > len_s - start)
		len = len_s - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*string;
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = gnl_strlen(s1);
	len_s2 = gnl_strlen(s2);
	string = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		string[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len_s2)
	{
		string[len_s1 + i] = s2[i];
		i++;
	}
	string[len_s1 + len_s2] = '\0';
	return (string);
}

char	*gnl_strdup(const char *s)
{
	char			*string;
	unsigned int	i;

	i = 0;
	string = malloc(sizeof(char) * (gnl_strlen(s) + 1));
	if (string == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		string[i] = s[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}
