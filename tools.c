/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:30:54 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:30:55 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	peek(char *str)
{
	while ((*str == ' ' || *str == '\t') && *str)
		str++;
	return (*str);
}

void	get_end(char **es)
{
	char	*tmp;
	int		j;
	char	c;

	tmp = *es;
	j = 2;
	while (*tmp != ' ' && *tmp != '\t' && *tmp != '|' && *tmp != '>'
		&& *tmp != '<' && *tmp != '\n' && *tmp)
	{
		if (*tmp == '\'' || *tmp == '"')
		{
			c = *tmp;
			j = 2;
			while (j)
			{
				if (*tmp == c)
					j--;
				tmp++;
			}
		}
		else
			tmp++;
	}
	*es = tmp;
}

int	do_scanner(char **tmp, char **e)
{
	int	return_value;

	if (**tmp == '"')
	{
		scanner_qoutes(tmp);
		get_end(tmp);
		*e = *tmp;
		return_value = 1;
		return (return_value);
	}
	else if (**tmp == '\'')
	{
		scanner_single(tmp);
		return_value = 2;
		get_end(tmp);
		*e = *tmp;
		return (return_value);
	}
	else
		*tmp = *tmp + 1;
	return (0);
}

int	scanner(char **string, char **s, char **e)
{
	char	*tmp;
	int		return_value;

	return_value = 0;
	tmp = *string;
	while ((*tmp == ' ' || *tmp == '\t') && *tmp)
		tmp++;
	if (s)
		*s = tmp;
	while ((*tmp != '$' && *tmp != ' ' && *tmp != '\t' \
	&& *tmp != '>' && *tmp != '|' && *tmp != '<') && *tmp && *tmp != '\n')
	{
		return_value = do_scanner(&tmp, e);
		if (return_value)
			return (return_value);
	}
	if (e)
		*e = tmp;
	*string = tmp;
	return (return_value);
}

char	**ft_realloc(char **ptr, int size)
{
	char	**tmp;

	tmp = ft_calloc((sizeof(char *)), size + 1);
	if (!tmp)
	{
		return (NULL);
	}
	if (ptr)
	{
		ft_memcpy(tmp, ptr, size * sizeof(char *));
		free(ptr);
	}
	return (tmp);
}
