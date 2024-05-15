/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:30:16 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:30:18 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_get_and_replace(char ***variables, int *number, t_string *s, t_n *n)
{
	int		t;
	int		len_string;
	char	*value_var;

	t = 0;
	len_string = ft_strlen(*(*variables + *number));
	value_var = *(*variables + *number);
	while (t < len_string)
	{
		*(s->new_string + n->i) = *(value_var + t);
		t++;
		n->i = n->i + 1;
	}
	if (*(s->tmp + n->j) == '$' && *(s->tmp + n->j + 1) == '?')
		n->j = n->j + 2;
	else
		n->j = n->j + get_lenght_variable(s->tmp + n->j + 1) + 1;
	*number = *number + 1;
}

void	get_and_replace(int len_malloc, char ***variables, t_string *s)
{
	int		number;
	char	*value_var;
	int		len_string;
	t_n		n;

	init_numbers(&number, &n);
	while (n.i < len_malloc)
	{
		if (*(s->tmp + n.j) == '$' && *(s->tmp + n.j + 1) == '?')
			do_get_and_replace(variables, &number, s, &n);
		else if ((*(s->tmp + n.j) == '$')
			&& (ft_isalpha(*(s->tmp + n.j + 1)) || *(s->tmp + n.j + 1) == '_'
				|| ft_isdigit(*(s->tmp + n.j + 1))))
		{
			do_get_and_replace(variables, &number, s, &n);
		}
		else
		{
			*(s->new_string + n.i) = *(s->tmp + n.j);
			(n.j)++;
			(n.i)++;
		}
	}
	*(s->new_string + n.i) = '\0';
}

int	do_handle_qoutes_string(char **str, char *tmp, char ***variables, int *size)
{
	int	i;
	int	len_malloc;

	i = 0;
	len_malloc = 0;
	while (*(tmp + i) != '"')
	{
		if ((*(tmp + i) == '$') && (*(tmp + i + 1) == '?'))
			handle_single_var(&i, &len_malloc, variables, size);
		else if ((*(tmp + i) == '$') && (ft_isalpha(*(tmp + i + 1))
				|| ft_isdigit(*(tmp + i + 1)) || *(tmp + i + 1) == '_'))
		{
			len_malloc += handle_var_name(tmp, &i, size, variables);
		}
		else
		{
			i++;
			len_malloc = len_malloc + 1;
		}
	}
	*str = tmp + i + 1;
	return (len_malloc);
}

char	*handler_space(char **str, char **tmp)
{
	while ((**tmp == ' ' || **tmp == '\t') && **tmp)
		(*tmp)++;
	(*tmp)++;
	if (**tmp == '"')
	{
		*str = *tmp + 1;
		return (ft_strdup("\0"));
	}
	else if (**tmp == '$' && *(*tmp + 1) == '"')
	{
		*str = *tmp + 2;
		return (ft_strdup("$"));
	}
	return (NULL);
}

char	*handle_qoutes_string(char **str, char c, char **env)
{
	int			len_malloc;
	char		**variables;
	int			size;
	t_string	s;

	s.tmp = *str;
	s.new_string = handler_space(str, &s.tmp);
	if (s.new_string)
		return (s.new_string);
	len_malloc = 0;
	size = 1;
	variables = NULL;
	len_malloc += do_handle_qoutes_string(str, s.tmp, &variables, &size);
	s.new_string = malloc(sizeof(char) * len_malloc + 1);
	if (!s.new_string)
		return (NULL);
	get_and_replace(len_malloc, &variables, &s);
	free_double_ptr(variables);
	return (s.new_string);
}
