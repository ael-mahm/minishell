/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:32:16 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:32:17 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fn_check_exec(char **str, int *v, char *end, char **start)
{
	char	*new_str;
	int		len;
	char	*var_name;
	char	*value_var;
	int		len_string;

	if (!(*v))
	{
		len = get_len_v_2(*start, end);
		new_str = get_string_move_start_2(start, end, len);
	}
	else if (*v == 1)
	{
		len = get_len_q_v1_new(*start, end, g_data.env_copy);
		new_str = get_string_q_v1_and_move(start, end, len, g_data.env_copy);
	}
	else if (*v == 2)
	{
		len = get_len_q_v4(*start);
		new_str = get_string_q_v4(start, len);
	}
	else if (*v == 4)
		new_str = get_new_str_v(str, g_data.env_copy, start);
	return (new_str);
}

int	set_v(char *start, int *v)
{
	if (*start == '\'')
		*v = 2;
	else if (*start == '"')
		*v = 1;
	else if (*start == ' ' || *start == '\t'
		|| *start == '\n' || *start == '\0')
	{
		*v = 5;
	}
	else if (*start == '$')
		*v = 4;
	else
		*v = 0;
	return (*v);
}

char	*function_four(char **str, char **env)
{
	char		*start;
	char		*end;
	int			v;
	char		*full_str;
	t_string	s;

	func_space(str, &start, &end);
	v = 4;
	full_str = ft_strdup("\0");
	while (!ft_isspace(*start) && *start != '\0' && *start != '>'
		&& *start != '<' && *start != '|')
	{
		s.tmp = full_str;
		s.new_string = fn_check_exec(str, &v, end, &start);
		full_str = ft_strjoin(full_str, s.new_string);
		set_v(start, &v);
		free_ptr(&s.new_string);
		free_ptr(&s.tmp);
		if (v == 5)
			break ;
	}
	*str = start;
	return (full_str);
}

char	*fn_check_exec_v(char **str, int *v, char *end, char **start)
{
	int		len;
	char	*new_str;
	char	*end_s;

	if (!(*v))
	{
		len = get_len_v_3(*start, end_s);
		new_str = get_string_move_start_2(start, end, len);
	}
	else if (*v == 1)
	{
		len = get_len_q_v1_new_2(*start, g_data.env_copy);
		new_str = get_string_q_v1_and_move_2(start, len, g_data.env_copy);
	}
	else if (*v == 2)
	{
		len = get_len_q_v4(*start);
		new_str = get_string_q_v4(start, len);
	}
	else if (*v == 4)
		new_str = get_new_str_v(str, g_data.env_copy, start);
	return (new_str);
}

char	*function_five(char **str, char **env)
{
	char		*full_str;
	int			v;
	char		*start;
	char		*end;
	t_string	s;

	v = scanner(str, &start, &end);
	full_str = ft_strdup("\0");
	while (!ft_isspace(*start) && *start != '\0'
		&& *start != '>' && *start != '<' && *start != '|')
	{
		s.tmp = full_str;
		s.new_string = fn_check_exec_v(str, &v, end, &start);
		full_str = ft_strjoin(full_str, s.new_string);
		free_ptr(&s.new_string);
		free_ptr(&s.tmp);
		set_v(start, &v);
		if (v == 5)
			break ;
	}
	*str = start;
	return (full_str);
}
