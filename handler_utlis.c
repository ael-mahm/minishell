/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:31:29 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:31:31 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*allocate_and_copy(int i, char *tmp)
{
	char	*new_str;
	int		j;

	new_str = malloc(sizeof(char) * i + 1);
	if (!new_str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		*(new_str + j) = *(tmp + j);
		j++;
	}
	*(new_str + j) = 0;
	return (new_str);
}

char	*get_name_variable(char *tmp, int i)
{
	int		j;
	char	*str;
	int		c;
	int		d;

	j = 0;
	i++;
	while (ft_isalpha(*(tmp + i + j))
		|| *(tmp + i + j) == '_' || ft_isdigit(*(tmp + i + j)))
	{
		j++;
	}
	str = malloc(sizeof(char) * j + 1);
	if (!str)
		return (NULL);
	d = 0;
	while (d < j)
	{
		*(str + d) = *(tmp + i + d);
		d++;
	}
	*(str + d) = 0;
	return (str);
}

int	get_lenght_variable(char *tmp)
{
	int	j;

	j = 0;
	while (ft_isalpha(*(tmp + j))
		|| ft_isdigit(*(tmp + j)) || *(tmp + j) == '_')
	{
		j++;
	}
	return (j);
}

char	*get_value_variable(char *var_name, char **env)
{
	size_t	len;
	size_t	i;
	char	*tmp;
	char	**ptr;
	char	*tmp2;

	len = ft_strlen(var_name);
	i = 0;
	while (*(env + i))
	{
		if (!ft_strncmp(*(env + i), var_name, len)
			&& *(*(env + i) + len) == '=')
		{
			tmp2 = ft_strchr(*(env + i), '=');
			tmp = ft_strdup(tmp2 + 1);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

char	*handle_single_string(char **str, char c, char **env)
{
	char	*tmp;
	char	*new_str;
	int		i;

	tmp = *str;
	while ((*tmp == ' ' || *tmp == '\t') && *tmp)
		tmp++;
	tmp++;
	i = 0;
	while (*(tmp + i) != c)
		i++;
	if (i == 0)
	{
		*str = tmp + i + 1;
		return (ft_strdup("\0"));
	}
	*str = tmp + i + 1;
	new_str = allocate_and_copy(i, tmp);
	return (new_str);
}
