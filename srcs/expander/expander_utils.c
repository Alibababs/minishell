/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:57:17 by alibabab          #+#    #+#             */
/*   Updated: 2024/12/09 16:57:39 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_single_quotes(char *str, char *ptr)
{
	int	in_single_quote;
	int	i;

	in_single_quote = 0;
	i = 0;
	while (str[i] && &str[i] < ptr)
	{
		if (str[i] == '\'')
			in_single_quote = !in_single_quote;
		i++;
	}
	return (in_single_quote);
}
