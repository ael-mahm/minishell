/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:36:38 by ael-mahm          #+#    #+#             */
/*   Updated: 2021/11/25 11:55:46 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	check_ch(char ch, char const *set)
{
	while (*set)
	{
		if (ch == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	size_s1;
	int	start;
	int	end;
	int	i;

	if (!s1 || !set)
		return (0);
	size_s1 = ft_strlen(s1);
	i = 0;
	start = 0;
	while (check_ch(s1[i], set))
	{
		start++;
		i++;
	}
	end = size_s1 - 1;
	while (check_ch(s1[end], set))
	{
		end--;
	}
	if (start > end)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start + 1));
}
