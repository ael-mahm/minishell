/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:13:08 by ael-mahm          #+#    #+#             */
/*   Updated: 2021/11/25 12:05:05 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const	*s, char (*f)(unsigned int, char))
{
	size_t	len_s;
	char	*ptr;
	int		i;

	if (!s || !f)
		return (0);
	len_s = ft_strlen(s);
	ptr = malloc((len_s + 1) * sizeof(char));
	if (!ptr)
		return (0);
	i = 0;
	while (*s)
	{
		*(ptr + i) = (*f)(i, *s);
		s++;
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
