/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utlis_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:34:18 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:34:19 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_q_v1_new_2(char *start, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	while (*start && j)
	{
		if (*start == '$')
			i += value_of_var(&start, env);
		else if (*start != '"')
		{
			i++;
			start++;
		}
		else
		{
			start++;
			j--;
		}
	}
	return (i + 1);
}

void	get_value_of_r_error_2(char **value_var, int *len_string, char **start)
{
	*start += 2;
	*value_var = get_value_of_exit();
	if (!(*value_var))
		*value_var = ft_strdup("\0");
	*len_string = ft_strlen(*value_var);
}

void	func_1_get_var(char **env, int *len_string, \
			char **value_var, char **m_start)
{
	char	*var_name;

	var_name = get_name_variable(*m_start, 0);
	*len_string = ft_strlen(var_name);
	if (*len_string == 0)
	{
		*m_start += (*len_string + 1);
		*len_string = 1;
		*value_var = ft_strdup("$");
	}
	else
	{
		*m_start += (*len_string + 1);
		*value_var = get_value_variable(var_name, env);
		if (!(*value_var))
			*value_var = ft_strdup("\0");
	}
	*len_string = ft_strlen(*value_var);
	free_ptr(&var_name);
}

void	copy_to_tmp_and_free(int *i, char **value_var, \
				char *tmp, int len_string)
{
	int	d;

	d = 0;
	while (d < len_string)
	{
		*(tmp + *i) = *(*value_var + d);
		d++;
		*i = *i + 1;
	}
	free_ptr(value_var);
}

void	check_and_set(char **env, char **m_start, t_n *n, char *tmp)
{
	char	*value_var;
	int		len_string;

	if (**m_start == '$')
	{
		if (*(*m_start + 1) == '?')
			get_value_of_r_error_2(&value_var, &len_string, m_start);
		else
			func_1_get_var(env, &len_string, &value_var, m_start);
		copy_to_tmp_and_free(&(n->i), &value_var, tmp, len_string);
	}
	else if (**m_start != '"')
	{
		*(tmp + n->i) = *(*m_start);
		n->i = n->i + 1;
		*m_start = *m_start + 1;
	}
	else
	{
		*m_start = *m_start + 1;
		n->j = n->j - 1;
	}
}
