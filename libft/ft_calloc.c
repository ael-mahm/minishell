/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:32:00 by ael-mahm          #+#    #+#             */
/*   Updated: 2021/11/25 14:27:13 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t	count, size_t	size)
{
	char	*ptr;

	ptr = malloc ((count * size) * sizeof(char));
	if (!ptr)
		return (0);
	ft_bzero (ptr, count * size);
	return (ptr);
}
