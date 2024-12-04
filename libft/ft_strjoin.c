/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:37:29 by phautena          #+#    #+#             */
/*   Updated: 2024/05/20 14:25:02 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	string = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		string[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		string[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	string[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (string);
}
