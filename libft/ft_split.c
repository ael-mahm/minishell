/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:58:01 by ael-mahm          #+#    #+#             */
/*   Updated: 2021/11/25 12:01:44 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_word(const char *str, char sp)
{
	int	index;

	index = 0;
	while (*str)
	{
		if (*str != sp)
		{
			while (*str != sp && *str)
				str++;
			index++;
		}
		else
			str++;
	}
	return (index);
}

int	ft_strlenght(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s == c)
		s++;
	while (*s != c && *s)
	{
		i++;
		s++;
	}
	return (i);
}

char	*split_word(int *ind, char const *s, char c)
{
	char	*ptr;
	int		i;

	ptr = malloc(ft_strlenght(&s[*ind], c) * sizeof(char) + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (s[*ind] == c)
		*ind = (*ind) + 1;
	while (s[*ind] != c && s[*ind])
	{
		*(ptr + i) = *(s + *ind);
		*ind = (*ind) + 1;
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}

char	**ft_split(char	const *s, char c)
{
	char	**ptr;
	int		i;
	int		j;
	int		index;

	if (!s)
		return (0);
	j = ft_word(s, c);
	ptr = malloc((j + 1) * sizeof(char *));
	if (!ptr)
		return (0);
	i = 0;
	index = 0;
	while (i < j)
	{
		ptr[i] = split_word(&index, s, c);
		i++;
	}
	*(ptr + i) = 0;
	return (ptr);
}
