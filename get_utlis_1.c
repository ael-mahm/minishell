/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utlis_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:32:32 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:32:33 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	value_of_var(char **start, char **env)
{
	char	*value_var;
	int		len_string;
	char	*var_name;

	if (*(*start + 1) == '?')
		value_of_single_var(start);
	else
	{
		var_name = get_name_variable(*start, 0);
		len_string = ft_strlen(var_name);
		*start += (len_string + 1);
		if (len_string == 0)
			len_string = 1;
		else
		{
			value_var = get_value_variable(var_name, env);
			if (!value_var)
				value_var = ft_strdup("\0");
			len_string = ft_strlen(value_var);
			free_ptr(&value_var);
		}
		free_ptr(&var_name);
	}
	return (len_string);
}

void	func_get_value_of_var(char **env, \
			char **start, int *len_s, char **value_v)
{
	char	*var_name;

	var_name = get_name_variable(*start, 0);
	*len_s = ft_strlen(var_name);
	*start += (*len_s + 1);
	if (*len_s == 0)
		*len_s = 1;
	else
	{
		*value_v = get_value_variable(var_name, env);
		if (!(*value_v))
			*value_v = ft_strdup("\0");
		*len_s = ft_strlen(*value_v);
		free_ptr(value_v);
	}
	free_ptr(&var_name);
}

void	get_value_of_r_error(char **value_var, int *len_string, char **start)
{
	*start += 2;
	*value_var = get_value_of_exit();
	if (!(*value_var))
		*value_var = ft_strdup("\0");
	*len_string = ft_strlen(*value_var);
	free_ptr(value_var);
}

void	increment(char **start, int *i, int *j)
{
	if (**start != '"')
	{
		*i = *i + 1;
		*start = *start + 1;
	}
	else
	{
		*start = *start + 1;
		*j = *j - 1;
	}
}

int	get_len_q_v1_new(char *start, char *end, char **env)
{
	int		i;
	int		j;
	int		len_string;
	char	*value_var;

	i = 0;
	j = 2;
	while (start < end && j)
	{
		if (*start == '$')
		{
			if (*(start + 1) == '?')
				get_value_of_r_error(&value_var, &len_string, &start);
			else
				func_get_value_of_var(env, &start, &len_string, &value_var);
			i += len_string;
		}
		else
			increment(&start, &i, &j);
	}
	return (i + 1);
}
