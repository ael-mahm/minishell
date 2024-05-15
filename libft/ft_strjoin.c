/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:08:35 by ael-mahm          #+#    #+#             */
/*   Updated: 2021/11/21 10:43:14 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const	*s1, char const	*s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	ptr = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		*(ptr + i) = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		*(ptr + i) = s2[j];
		i++;
		j++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
