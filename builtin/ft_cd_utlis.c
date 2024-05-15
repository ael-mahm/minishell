/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utlis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:28:34 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:28:36 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_v(void)
{
	char	*cur_pwd;

	cur_pwd = getcwd(NULL, 0);
	if (!cur_pwd)
		return ;
	ft_putendl_fd(cur_pwd, 1);
	free_ptr(&cur_pwd);
}

char	*get_value_of_env(char ***env, char *str)
{
	int		exist;
	char	**ptr;
	char	*tmp;
	char	*tmp1;

	exist = check_if_exist_v1(str, env);
	if (exist == -1)
		return (NULL);
	ptr = ft_split(*(*(env) + exist), '=');
	if (!ptr)
		return (NULL);
	else if (number_of_var(ptr) < 2)
	{
		free_double_ptr(ptr);
		return (ft_strdup("\0"));
	}
	tmp = ft_strchr(*(*(env) + exist), '=');
	tmp1 = ft_strdup(tmp + 1);
	free_double_ptr(ptr);
	return (tmp1);
}

int	check_errors(t_cmd *cmd)
{
	int	size;

	size = number_of_var(cmd->args);
	if (size == 2)
	{
		if (*(*(cmd->args + 1)) == '-' && *(*(cmd->args + 1) + 1) != '\0')
		{
			g_data.r_error = 2;
			ft_putstr_fd("[+ \033[31mERROR\033[0m +] cd: invalid option\n", 2);
			ft_putendl_fd("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]", 2);
			return (2);
		}
	}
	else if (size > 2)
	{
		g_data.r_error = 1;
		ft_putendl_fd("[+ \033[31mERROR\033[0m +] cd: too many arguments", 2);
		return (1);
	}
	return (0);
}

int	check_e(char ***env, t_cmd *cmd)
{
	int	return_value;

	return_value = 0;
	if (!(env) || !cmd)
	{
		g_data.r_error = 1;
		ft_putendl_fd("[+ \033[31mERROR\033[0m +] with env", 2);
		return (1);
	}
	return_value = check_errors(cmd);
	return (return_value);
}
