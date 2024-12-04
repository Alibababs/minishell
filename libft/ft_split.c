/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:01:31 by phautena          #+#    #+#             */
/*   Updated: 2024/05/29 10:13:29 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_var(size_t *i, int *j, int *start_word)
{
	*i = 0;
	*j = 0;
	*start_word = -1;
}

static int	word_count(const char *s, char c)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	while (*s != '\0')
	{
		if (*s != c && x == 0)
		{
			x = 1;
			count++;
		}
		else if (*s == c)
			x = 0;
		s++;
	}
	return (count);
}

static void	*ft_free(char **res, int word_count)
{
	int	i;

	i = 0;
	while (i < word_count)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

static char	*fill_word(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc((end - start + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = s[start];
		start++;
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	i;
	int		j;
	int		start_word;

	res = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (res == NULL)
		return (NULL);
	init_var(&i, &j, &start_word);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start_word < 0)
			start_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start_word >= 0)
		{
			res[j] = fill_word(s, start_word, i);
			if (res[j] == NULL)
				return (ft_free(res, j));
			start_word = -1;
			j++;
		}
		i++;
	}
	return (res);
}
