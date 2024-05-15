/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:36:28 by ael-mahm          #+#    #+#             */
/*   Updated: 2021/11/29 11:17:42 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst > src)
	{
		ptr1 = (unsigned char *)dst + len -1;
		ptr2 = (unsigned char *)src + len - 1;
		while (len-- > 0)
		{
			*ptr1 = *ptr2;
			ptr1--;
			ptr2--;
		}
	}
	else
	{
		ptr1 = (unsigned char *)dst;
		ptr2 = (unsigned char *)src;
		while (len-- > 0)
			*ptr1++ = *ptr2++;
	}
	return ((void *)dst);
}
