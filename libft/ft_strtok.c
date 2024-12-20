/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:10:12 by alibabab          #+#    #+#             */
/*   Updated: 2024/12/20 21:54:30 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*skip_delim(char *str, char delim)
{
	while (*str == delim)
		str++;
	return (str);
}

char	*ft_strtok(char *str, char *delim)
{
	static char	*last = NULL;
	char		*start;

	if (str == NULL)
		str = last;
	str = skip_delim(str, *delim);
	if (*str == '\0')
		return (NULL);
	start = str;
	while (*str != '\0' && *str != *delim)
		str++;
	if (*str == '\0')
		last = str;
	else
	{
		*str = '\0';
		last = str + 1;
	}
	return (start);
}
