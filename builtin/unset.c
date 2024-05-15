/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:29:09 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:29:10 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_exist_v1(char *str, char ***env)
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
				return (i);
		}
		i++;
	}
	return (-1);
}

void	ft_remove(char ***env, t_cmd *cmd, int *j)
{
	int	exist;
	int	env_size;

	if (check_valid_name(*(cmd->args + *j)))
	{
		exist = check_if_exist_v1(*(cmd->args + *j), env);
		env_size = number_of_var(*env);
		if (exist != -1)
		{
			free(*(*env + exist));
			while (exist < env_size - 1)
			{
				*(*env + exist) = *(*env + exist + 1);
				exist++;
			}
			*(*env + exist) = NULL;
		}
	}
	else
		g_data.r_error = 1;
}

int	check_and_delete(t_cmd *cmd, char ***env, size_t argv_size)
{
	int		j;
	int		exist;
	size_t	env_size;

	j = 1;
	g_data.r_error = 0;
	while (j <= argv_size)
	{
		ft_remove(env, cmd, &j);
		j++;
	}
	return (1);
}

int	unset(t_cmd *cmd)
{
	size_t	j;
	size_t	argv_size;

	g_data.r_error = 0;
	if (!g_data.env_copy || !cmd)
	{
		g_data.r_error = 1;
		return (1);
	}
	if (*(cmd->args + 1) == NULL)
		return (0);
	argv_size = number_of_var(cmd->args + 1);
	check_and_delete(cmd, &g_data.env_copy, argv_size);
	return (g_data.r_error);
}
