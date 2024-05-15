/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:46:04 by ael-mahm          #+#    #+#             */
/*   Updated: 2021/11/29 11:18:23 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char	*src, size_t dstsize)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	i;

	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (lendst >= dstsize)
		return (dstsize + lensrc);
	i = 0;
	while (i < lensrc && lendst + i < dstsize - 1)
	{
		*(dst + lendst + i) = *(src + i);
		i++;
	}
	*(dst + lendst + i) = '\0';
	return (lendst + lensrc);
}
