/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:22:21 by phautena          #+#    #+#             */
/*   Updated: 2024/05/17 18:07:31 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_cvt;
	unsigned char	c_cvt;
	size_t			i;

	s_cvt = (unsigned char *) s;
	c_cvt = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (s_cvt[i] == c_cvt)
			return ((void *)(s_cvt + i));
		i++;
	}
	return (NULL);
}
