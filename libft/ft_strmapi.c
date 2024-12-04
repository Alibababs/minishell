/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:46:42 by phautena          #+#    #+#             */
/*   Updated: 2024/05/24 13:12:10 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*string;
	int		i;

	string = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (string == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		string[i] = (*f)(i, s[i]);
		i++;
	}
	string[i] = '\0';
	return (string);
}
