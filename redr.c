/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:30:44 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:30:45 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_NODE	*do_create_redr_node(t_REDR_CMD *tmp)
{
	t_value	*ptr;
	t_NODE	*exc_cmd;

	ptr = malloc(sizeof(t_value));
	if (!ptr)
	{
		free(tmp);
		return (NULL);
	}
	ptr->redr_cmd = tmp;
	exc_cmd = malloc(sizeof(t_NODE));
	if (!exc_cmd)
	{
		free(tmp);
		free(ptr);
		return (NULL);
	}
	exc_cmd->type = REDR;
	exc_cmd->value = ptr;
	exc_cmd->next = NULL;
	return (exc_cmd);
}

t_NODE	*create_redr_node(char **ptr_2, char type_redr)
{
	t_REDR_CMD	*tmp;
	t_NODE		*exc_cmd;

	if (!ptr_2)
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] ", 2);
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
		return (NULL);
	}
	tmp = malloc(sizeof(t_REDR_CMD));
	if (!tmp)
		return (NULL);
	tmp->list_file_name = ptr_2;
	tmp->type_redr = type_redr;
	exc_cmd = do_create_redr_node(tmp);
	return (exc_cmd);
}

void	func1(char *tmp, int *i, int *size, char **env)
{
	char	*var_name;
	char	*value_var;
	int		len_string;

	var_name = get_name_variable(tmp + *i, 0);
	if (*var_name == '\0')
	{
		*size += 1;
		*i += 1;
	}
	else
	{
		len_string = ft_strlen(var_name);
		*i += len_string + 1;
		value_var = get_value_variable(var_name, env);
		if (value_var)
			*size = *size + ft_strlen(value_var);
		free_ptr(&value_var);
	}
	free_ptr(&var_name);
}

void	func2(char *tmp, t_n *n, char *return_value, char **env)
{
	char	*var_name;
	char	*value_var;
	int		len_string;
	int		k;

	var_name = get_name_variable(tmp + n->i, 0);
	if (*var_name == '\0')
	{
		*(return_value + (n->j)++) = '$';
		(n->i)++;
	}
	else
	{
		len_string = ft_strlen(var_name);
		n->i += len_string + 1;
		value_var = get_value_variable(var_name, env);
		if (value_var)
		{
			k = 0;
			while (*(value_var + k))
				*(return_value + (n->j)++) = *(value_var + k++);
		}
	}
}

char	*get_line(char *tmp, char **env)
{
	int		size;
	char	*return_value;
	t_n		n;

	size = 0;
	return_value = NULL;
	size = get_size_of_line(tmp, env);
	return_value = malloc(size * sizeof(char) + 1);
	if (!return_value)
	{
		perror("bash: ");
		return (NULL);
	}
	n.i = 0;
	n.j = 0;
	while (*(tmp + n.i))
	{
		if (*(tmp + n.i) == '$')
			func2(tmp, &n, return_value, env);
		else
			*(return_value + (n.j)++) = *(tmp + (n.i)++);
	}
	*(return_value + n.j) = '\0';
	return (return_value);
}
