/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:40:01 by ael-mahm          #+#    #+#             */
/*   Updated: 2021/11/18 11:52:26 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = dstsize - 1;
	if (dstsize > 0)
	{
		while (*(src + i) && i < size)
		{
			*(dst + i) = *(src + i);
			i++;
		}
	*(dst + i) = '\0';
	}
	return (ft_strlen(src));
}
