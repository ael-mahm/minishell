/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:16:56 by ael-mahm          #+#    #+#             */
/*   Updated: 2021/11/18 12:30:19 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ptr;

	if (c == 0)
		return ((char *)s + ft_strlen(s));
	ptr = NULL;
	while (*s)
	{
		if (*s == (char) c)
		{
			ptr = s;
		}
		s++;
	}
	return ((char *)ptr);
}
