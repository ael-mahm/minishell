/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:29:56 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:29:57 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**count_and_alloc(char **env)
{
	char	**return_value;
	size_t	i;

	i = 0;
	while (*(env + i))
		i++;
	return_value = malloc(((i + 1) * sizeof(char *)));
	return (return_value);
}

char	**duplicate_env(char **env)
{
	char	**return_value;
	char	*dup_str;
	size_t	i;

	if (!env)
		return (NULL);
	return_value = count_and_alloc(env);
	if (!return_value)
		return (NULL);
	i = 0;
	while (*(env + i))
	{
		dup_str = ft_strdup(*(env + i));
		if (!dup_str)
		{
			*(return_value + i) = dup_str;
			free_double_ptr(return_value);
			return (NULL);
		}
		*(return_value + i) = dup_str;
		i++;
	}
	*(return_value + i) = 0;
	return (return_value);
}
