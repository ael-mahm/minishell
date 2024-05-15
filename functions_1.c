/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:34:02 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:34:03 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name_and_value(char **str, char **env)
{
	char	*start;
	int		k;
	int		len_string;
	char	*var_name;
	char	*value_var;

	k = 0;
	start = *str;
	var_name = get_name_variable(start, k);
	len_string = ft_strlen(var_name);
	k += len_string + 1;
	value_var = get_value_variable(var_name, env);
	if (!value_var)
		value_var = ft_strdup("\0");
	start = start + k;
	*str = start;
	free_ptr(&var_name);
	return (value_var);
}

char	*get_new_str(char **str, char **env)
{
	char	*start;
	char	*new_str;

	if (**str == '$' && *(*str + 1) == '?')
	{
		start = *str;
		start = start + 2;
		new_str = get_value_of_exit();
		*str = start;
	}
	else if (**str == '$' && (!ft_isalpha(*(*str + 1))
			&& !ft_isdigit(*(*str + 1)) && *(*str + 1) != '_'))
	{
		start = *str;
		start = start + 1;
		new_str = ft_strdup("$");
		*str = start;
	}
	else
		new_str = name_and_value(str, env);
	return (new_str);
}

char	*check_and_get_new_str(char **str, char **env)
{
	char	*new_str;
	int		len;

	if (**str == '"')
		new_str = handle_qoutes_string(str, '"', env);
	else if (**str == '\'')
		new_str = handle_single_string(str, '\'', env);
	else if (**str == '$')
		new_str = get_new_str(str, env);
	else
	{
		len = get_len_of_string(str);
		new_str = get_str(str, len);
	}
	return (new_str);
}

char	*function_three(char **str, char **env, char c)
{
	char	*full_str;
	char	*new_str;
	int		len;
	char	*t;

	full_str = ft_strdup("\0");
	if (c == '"')
		new_str = handle_qoutes_string(str, '"', env);
	else
		new_str = handle_single_string(str, '\'', env);
	t = full_str;
	full_str = ft_strjoin(full_str, new_str);
	free_ptr(&t);
	free_ptr(&new_str);
	while ((**str == '\'' || **str == '"') || (!ft_isspace(**str)
			&& **str != '<' && **str != '>' && **str != '|'
			&& **str != '\n' && **str != '\0'))
	{
		new_str = check_and_get_new_str(str, env);
		t = full_str;
		full_str = ft_strjoin(full_str, new_str);
		free_ptr(&t);
		free_ptr(&new_str);
	}
	return (full_str);
}
