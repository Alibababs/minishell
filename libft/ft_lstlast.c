/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:34:02 by phautena          #+#    #+#             */
/*   Updated: 2024/05/28 11:39:50 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;
	int		i;

	i = ft_lstsize(lst);
	ptr = lst;
	while (i > 1)
	{
		ptr = ptr->next;
		i--;
	}
	return (ptr);
}
