/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:10:06 by phautena          #+#    #+#             */
/*   Updated: 2024/05/17 16:20:00 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;

	dst_tmp = (unsigned char *) dst;
	src_tmp = (unsigned char *) src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n-- > 0)
	{
		*dst_tmp = *src_tmp;
		dst_tmp++;
		src_tmp++;
	}
	return (dst);
}
