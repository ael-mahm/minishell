/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:34:35 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:34:35 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_of_exit(void)
{
	char	*tmp;

	tmp = ft_itoa(g_data.r_error);
	return (tmp);
}

int	ft_isspace(char tmp)
{
	if (tmp == ' ' || tmp == '\t' || tmp == '\f' || tmp == '\v' || tmp == '\r')
		return (1);
	return (0);
}

void	scanner_qoutes(char **es)
{
	char	*str;

	str = *es;
	str++;
	while (*str != '"')
		str++;
	str++;
	*es = str;
}

void	scanner_single(char **es)
{
	char	*str;

	str = *es;
	str++;
	while (*str != '\'')
		str++;
	str++;
	*es = str;
}

void	func_space(char **str, char **start, char **end)
{
	int	k;

	k = 0;
	*start = *str;
	while (ft_isspace(*(*start + k)))
		k++;
	*start = *start + k;
	*end = *start;
	get_end(end);
}
