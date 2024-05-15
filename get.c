/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:30:06 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:30:07 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_string_q_v1_and_move_2(char **start, int size, char **env)
{
	char	*tmp;
	int		len_string;
	char	*value_var;
	char	*m_start;
	t_n		n;

	tmp = malloc(size * sizeof(char));
	if (!tmp)
		return (NULL);
	n.i = 0;
	m_start = *start;
	n.j = 2;
	value_var = NULL;
	while (*m_start && n.j)
	{
		check_and_set(env, &m_start, &n, tmp);
	}
	*(tmp + n.i) = 0;
	*start = m_start;
	return (tmp);
}

char	*get_string_q_v1_and_move(char **start, char *end, int size, char **env)
{
	char	*tmp;
	char	*m_start;
	t_n		n;

	tmp = malloc(size * sizeof(char));
	if (!tmp)
		return (NULL);
	n.i = 0;
	m_start = *start;
	n.j = 2;
	while (m_start < end && n.j)
	{
		check_and_set(env, &m_start, &n, tmp);
	}
	*(tmp + n.i) = 0;
	*start = m_start;
	return (tmp);
}

int	get_len_v_3(char *start, char *end)
{
	int	i;

	i = 0;
	while (*start)
	{
		start++;
		i++;
		if (*start == '\'' || *start == '"' || *start == '$'
			|| ft_isspace(*start) || *start == '|' || *start == '>'
			|| *start == '<')
			break ;
	}
	return (i + 1);
}

int	get_len_v_2(char *start, char *end)
{
	int	i;

	i = 0;
	while (start < end)
	{
		start++;
		i++;
		if (*start == '\'' || *start == '"' || *start == '$')
			break ;
	}
	return (i + 1);
}

char	*get_string_move_start_2(char **start, char *end, int size)
{
	char	*tmp;
	char	*m_start;
	int		i;

	m_start = *start;
	tmp = malloc(size * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	size--;
	while (*m_start && size)
	{
		*(tmp + i) = *(m_start);
		m_start++;
		i++;
		size--;
	}
	*(tmp + i) = 0;
	*start = m_start;
	return (tmp);
}
