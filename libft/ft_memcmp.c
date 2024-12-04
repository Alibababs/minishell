/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:05:31 by phautena          #+#    #+#             */
/*   Updated: 2024/05/17 18:06:32 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_cvt;
	unsigned char	*s2_cvt;
	size_t			i;

	s1_cvt = (unsigned char *) s1;
	s2_cvt = (unsigned char *) s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s1_cvt[i] != s2_cvt[i])
		{
			return (s1_cvt[i] - s2_cvt[i]);
		}
		i++;
	}
	return (0);
}
