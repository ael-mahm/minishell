/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:48:04 by ael-mahm          #+#    #+#             */
/*   Updated: 2021/11/25 13:51:49 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char	*s1)
{
	size_t	len_s1;
	size_t	i;
	char	*ptr;

	len_s1 = ft_strlen(s1);
	ptr = malloc(len_s1 * sizeof(char) + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (i < len_s1)
	{
		*(ptr + i) = *(s1 + i);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
