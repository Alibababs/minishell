/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:31:16 by phautena          #+#    #+#             */
/*   Updated: 2024/05/24 13:10:51 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*dst_ptr;
	char	*src_ptr;
	size_t	i;

	dst_ptr = (char *)dst;
	src_ptr = (char *)src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst_ptr > src_ptr)
	{
		while (n-- > 0)
			dst_ptr[n] = src_ptr[n];
	}
	else
	{
		while (i < n)
		{
			dst_ptr[i] = src_ptr[i];
			i++;
		}
	}
	return (dst);
}
