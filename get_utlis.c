/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utlis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:31:15 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:31:17 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_of_string(char **str)
{
	char	*tmp;
	int		i;

	tmp = *str;
	i = 0;
	while (*tmp != '"' && *tmp != '\'' && *tmp != ' '
		&& *tmp != '>' && *tmp != '<' && *tmp != '|'
		&& *tmp != '\n' && *tmp != '\0' && *tmp != '$')
	{
		tmp++;
		i++;
	}
	return (i + 1);
}

char	*get_str(char **str, int size)
{
	char	*tmp;
	int		i;
	char	*m_start;

	tmp = malloc(size * sizeof(char));
	i = 0;
	m_start = *str;
	size--;
	while ((*m_start != '"' && *m_start != '\'' && *m_start != ' ' \
	&& *m_start != '>' && *m_start != '<' && *m_start != '|' \
	&& *m_start != '\n' && *m_start != '$') && size)
	{
		*(tmp + i) = *(m_start);
		m_start++;
		i++;
		size--;
	}
	*(tmp + i) = 0;
	*str = m_start;
	return (tmp);
}

int	get_len_q_v4(char *start)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	while (j)
	{
		if (*start != '\'')
		{
			i++;
		}
		else
			j--;
		start++;
	}
	return (i + 1);
}

char	*get_string_q_v4(char **start, int size)
{
	char	*tmp;
	int		i;
	int		j;
	char	*m_start;

	tmp = malloc(size * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 2;
	m_start = *start;
	while (*m_start && j)
	{
		if (*m_start != '\'')
		{
			*(tmp + i) = *(m_start);
			i++;
		}
		else
			j--;
		m_start++;
	}
	*(tmp + i) = 0;
	*start = m_start;
	return (tmp);
}

void	value_of_single_var(char **start)
{
	char	*value_var;
	int		len_string;

	*start += 2;
	value_var = get_value_of_exit();
	if (!value_var)
		value_var = ft_strdup("\0");
	len_string = ft_strlen(value_var);
	free_ptr(&value_var);
}
