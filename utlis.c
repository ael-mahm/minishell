/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:33:37 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:33:38 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name_and_value_v(char **str, char **env, char **start)
{
	int		k;
	int		len_string;
	char	*var_name;
	char	*new_str;
	char	*value_var;

	k = 0;
	var_name = NULL;
	value_var = NULL;
	var_name = get_name_variable(*start, k);
	len_string = ft_strlen(var_name);
	k += len_string + 1;
	if (len_string == 0)
		new_str = ft_strdup("$");
	else
	{
		value_var = get_value_variable(var_name, env);
		if (!value_var)
			new_str = ft_strdup("\0");
		else
			new_str = value_var;
	}
	free_ptr(&var_name);
	*start = *start + k;
	return (new_str);
}

char	*get_new_str_v(char **str, char **env, char **start)
{
	char	*new_str;
	int		k;
	char	*var_name;
	char	*value_var;
	int		len_string;

	if (**start == '$' && ((*(*start + 1) == '\0'
				|| (!ft_isalpha(*(*start + 1)) && *(*start + 1) != '_'))
			|| ft_isdigit(*(*start + 1))) && *(*start + 1) != '?')
	{
		*start = *start + 1;
		new_str = ft_strdup("$");
	}
	else if (**start == '$' && *(*start + 1) == '?')
	{
		*start = *start + 2;
		new_str = get_value_of_exit();
	}
	else
		new_str = name_and_value_v(str, env, start);
	return (new_str);
}

char	**get_files(char **str, char c, char **env)
{
	char	**ptr;
	int		i;
	char	*full_str;

	i = 1;
	ptr = NULL;
	full_str = NULL;
	while (c && !ft_isspace(c) && c != '\n' && c != '|' && c != '<' && c != '>')
	{
		if (c == '"')
			full_str = function_three(str, env, c);
		else if (c == '\'')
			full_str = function_three(str, env, c);
		else if (c == '$')
			full_str = function_four(str, env);
		else
			full_str = function_five(str, env);
		ptr = ft_realloc(ptr, i + 1);
		*(ptr + i - 1) = full_str;
		i++;
		c = peek(*str);
	}
	return (ptr);
}
