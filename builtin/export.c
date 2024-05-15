/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:28:09 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:28:12 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	check_valid_name_v1(char *str)
{
	size_t	i;

	if ((*str < 'A' || *str > 'Z') && (*str < 'a' || *str > 'z') \
	&& *str != '_')
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	i = 1;
	while (*(str + i) && *(str + i) != '=')
	{
		if ((*(str + i) < 'A' || *(str + i) > 'Z') \
		&& (*(str + i) < 'a' || *(str + i) > 'z') \
		&& (*(str + i) < '0' || *(str + i) > '9') && *(str + i) != '_')
		{
			ft_putstr_fd("[+ \033[31mERROR\033[0m +] export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}


int	check_if_exist(char *str, char ***env)
{
	size_t	i;
	size_t	len_str;

	i = 0;
	len_str = ft_strlen(str);
	while (*(*env + i))
	{
		if (!ft_strncmp(*(*env + i), str, len_str))
		{
			if (*(*(*env + i) + len_str) == '=')
			{
				free(*(*env + i));
				*(*env + i) = NULL;
				return (i);
			}
		}
		i++;
	}
	return (-1);
}

int	check_and_print(t_cmd *cmd, char ***env, size_t *argv_size)
{
	*argv_size = 0;
	g_data.r_error = 0;
	if (!env || !cmd)
	{
		g_data.r_error = 1;
		return (0);
	}
	else if (*(cmd->args + 1) == NULL)
	{
		print_declare_x(cmd, *env);
		if (cmd->out_file > 0)
			close (cmd->out_file);
		return (0);
	}
	*argv_size = number_of_var(cmd->args + 1);
	return (1);
}

int	export(t_cmd *cmd)
{
	char	**tmp;
	size_t	j;
	size_t	argv_size;

	if (!check_and_print(cmd, &g_data.env_copy, &argv_size))
		return (1);
	j = 1;
	while (j <= argv_size)
	{
		if (check_valid_name_v1(*(cmd->args + j)))
		{
			tmp = ft_split(*(cmd->args + j), '=');
			if (!tmp)
				return (1);
			else
				add(*(tmp + 0), &(g_data.env_copy), 
				number_of_var((g_data.env_copy)), *(cmd->args + j));
			free_double_ptr(tmp);
		}
		else
			g_data.r_error = 1;
		j++;
	}
	return (g_data.r_error);
}

void	add(char *tmp, char ***env, int env_size, char *str)
{
	char	**ptr;
	size_t	len;
	int		exist;

	if (check_valid_name(tmp))
	{
		len = ft_strlen(tmp);
		if (*(str + len) == '=')
		{
			exist = check_if_exist(tmp, env);
			if (exist == -1)
			{
				ptr = ft_realloc(*env, env_size + 1);
				*(ptr + env_size) = ft_strdup(str);
				*env = ptr;
			}
			else
			{
				free(*(*env + exist));
				*(*env + exist) = ft_strdup(str);
			}
		}
	}
}
