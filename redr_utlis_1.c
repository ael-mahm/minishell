/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redr_utlis_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:33:22 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:33:23 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size_of_line(char *tmp, char **env)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (*(tmp + i))
	{
		if (*(tmp + i) == '$')
			func1(tmp, &i, &size, env);
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

t_NODE	*create_redr(char **str, char **env)
{
	t_NODE	*exc_cmd;
	char	*tmp_str;
	int		c;
	char	**ptr_2;

	tmp_str = *str;
	ptr_2 = NULL;
	while (ft_isspace(*tmp_str) && *tmp_str)
		tmp_str++;
	if (*tmp_str == '<')
		tmp_str++;
	*str = tmp_str;
	if (*tmp_str == '<')
	{
		exc_cmd = create_redr_4(str, env);
		return (exc_cmd);
	}
	if (checkone(str))
		return (NULL);
	c = peek(*str);
	ptr_2 = get_files(str, c, env);
	exc_cmd = create_redr_node(ptr_2, '<');
	if (!exc_cmd)
		free_double_ptr(ptr_2);
	return (exc_cmd);
}

t_NODE	*create_redr_4(char **str, char **env)
{
	t_NODE	*exc_cmd;
	char	*tmp_str;
	int		c;
	char	**ptr_2;

	tmp_str = *str;
	ptr_2 = NULL;
	if (*tmp_str == '<')
		tmp_str++;
	*str = tmp_str;
	if (check_errors_rd4(str))
		return (NULL);
	c = peek(*str);
	ptr_2 = get_files(str, c, env);
	exc_cmd = create_redr_node(ptr_2, '-');
	if (!exc_cmd)
		free_double_ptr(ptr_2);
	return (exc_cmd);
}

t_NODE	*create_redr_2(char **str, char **env)
{
	t_NODE	*exc_cmd;
	char	*tmp_str;
	int		c;
	char	**ptr_2;

	tmp_str = *str;
	ptr_2 = NULL;
	while ((*tmp_str == ' ' || *tmp_str == '\t') && *tmp_str)
		tmp_str++;
	if (*tmp_str == '>')
		tmp_str++;
	*str = tmp_str;
	if (*tmp_str == '>')
	{
		exc_cmd = create_redr_3(str, env);
		return (exc_cmd);
	}
	if (checkone(str))
		return (NULL);
	c = peek(*str);
	ptr_2 = get_files(str, c, env);
	exc_cmd = create_redr_node(ptr_2, '>');
	if (!exc_cmd)
		free_double_ptr(ptr_2);
	return (exc_cmd);
}

t_NODE	*create_redr_3(char **str, char **env)
{
	t_NODE	*exc_cmd;
	char	*tmp_str;
	int		c;
	char	**ptr_2;

	tmp_str = *str;
	ptr_2 = NULL;
	if (*tmp_str == '>')
		tmp_str++;
	*str = tmp_str;
	if (check_err(tmp_str, str))
		return (NULL);
	c = peek(*str);
	ptr_2 = get_files(str, c, env);
	exc_cmd = create_redr_node(ptr_2, '+');
	if (!exc_cmd)
		free_double_ptr(ptr_2);
	return (exc_cmd);
}
