/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utlis_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:32:48 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:32:49 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_var(int *i, int *len_malloc, char ***variables, int *size)
{
	int		len_string;
	char	*value_var;

	len_string = 1;
	*i += len_string + 1;
	value_var = get_value_of_exit();
	if (!value_var)
		value_var = ft_strdup("\0");
	len_string = ft_strlen(value_var);
	*len_malloc += len_string;
	*variables = ft_realloc(*variables, *size);
	*(*variables + *size - 1) = value_var;
	*size = *size + 1;
}

int	handle_var_name(char *tmp, int *i, int *size, char ***variables)
{
	char	*var_name;
	int		len_string;
	char	*value_var;
	int		len_malloc;

	len_malloc = 0;
	var_name = get_name_variable(tmp, *i);
	len_string = ft_strlen(var_name);
	*i += len_string + 1;
	value_var = get_value_variable(var_name, g_data.env_copy);
	if (!value_var)
		value_var = ft_strdup("\0");
	len_string = ft_strlen(value_var);
	len_malloc += len_string;
	*variables = ft_realloc(*variables, *size);
	*(*variables + *size - 1) = value_var;
	*size = *size + 1;
	free_ptr(&var_name);
	return (len_malloc);
}

void	init_numbers(int *number, t_n *n)
{
	*number = 0;
	n->j = 0;
	n->i = 0;
}
