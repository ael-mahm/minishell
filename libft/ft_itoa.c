/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:20:33 by ael-mahm          #+#    #+#             */
/*   Updated: 2021/11/29 11:14:52 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(long n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void	ft_str_rev(char	*src)
{
	size_t	i;
	size_t	len_src;
	size_t	len_s;
	char	swap;

	len_src = ft_strlen(src) - 1;
	len_s = ft_strlen(src) - 1;
	i = 0;
	while (i <= (len_src / 2))
	{
		swap = src[i];
		src[i] = src[len_s];
		src[len_s] = swap;
		i++;
		len_s--;
	}
}

void	get_string_s(char *ptr, long nb, int sign)
{
	int	i;

	i = 0;
	while (nb != 0)
	{
		ptr[i++] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (sign < 0)
		ptr[i++] = '-';
	ptr[i] = '\0';
}

char	*ft_itoa(int n)
{
	int		len_n;
	char	*ptr;
	long	nb;
	int		sign;

	nb = n;
	sign = 0;
	len_n = count(nb);
	if (n == 0)
		return (ft_strdup("0"));
	if (nb < 0)
	{
		len_n += 1;
		nb *= -1;
		sign = -1;
	}
	ptr = malloc ((len_n + 1) * sizeof(char));
	if (!ptr)
		return (0);
	get_string_s(ptr, nb, sign);
	ft_str_rev(ptr);
	return (ptr);
}
