/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:23:22 by phautena          #+#    #+#             */
/*   Updated: 2024/05/21 16:27:46 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	long	nb;
	int		len;

	nb = n;
	len = 0;
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	if (nb == 0)
		len++;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	int		i;
	char	*result;

	nb = n;
	len = int_len(nb);
	i = len - 1;
	result = malloc(sizeof(char) * len + 1);
	if (result == NULL)
		return (NULL);
	result[0] = '0';
	if (nb < 0)
	{
		result[0] = '-';
		nb *= -1;
	}
	while (nb != 0)
	{
		result[i] = (nb % 10) + 48;
		nb /= 10;
		i--;
	}
	result[len] = '\0';
	return (result);
}
