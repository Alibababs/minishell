/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:41:07 by phautena          #+#    #+#             */
/*   Updated: 2024/05/29 10:30:40 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_item;
	void	*temp;

	if (lst == NULL || (*f) == NULL || (*del) == NULL)
		return (NULL);
	new_list = NULL;
	while (lst != NULL)
	{
		temp = (*f)(lst->content);
		new_item = ft_lstnew(temp);
		if (new_item == NULL)
		{
			(*del)(temp);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_item);
		lst = lst->next;
	}
	return (new_list);
}
