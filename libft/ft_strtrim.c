/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:28:25 by phautena          #+#    #+#             */
/*   Updated: 2024/05/30 09:57:38 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*string;
	size_t	start;
	size_t	end;

	string = 0;
	if (s1 != NULL && set != NULL)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (s1[end - 1] && ft_strrchr(set, s1[end - 1]) && end > start)
			end--;
		string = malloc(sizeof(char) * (end - start + 1));
		if (string == NULL)
			return (NULL);
		else
			ft_strlcpy(string, &s1[start], end - start + 1);
	}
	return (string);
}
