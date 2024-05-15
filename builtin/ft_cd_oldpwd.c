/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_oldpwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:27:36 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:27:38 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_sys(char *path, char **pwwd)
{
	g_data.r_error = 0;
	*pwwd = getcwd(NULL, 0);
	if (*path == '\0')
		return (0);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] cd: ", 2);
		perror(path);
		free_ptr(pwwd);
		g_data.r_error = 1;
		return (g_data.r_error);
	}
	return (0);
}

void	change_old_pwd(char **value, char *pwwd, char ***env)
{
	char	*cur_pwd;
	char	*tmp;
	int		sig;

	free_ptr(value);
	sig = 0;
	*value = get_value_of_env(&g_data.env_copy, "OLDPWD");
	if (*value || g_data.pwd_s == 0)
	{
		cur_pwd = get_value_of_env(&g_data.env_copy, "PWD");
		if (!cur_pwd)
		{
			cur_pwd = pwwd;
			sig = 1;
		}
		tmp = ft_strjoin("OLDPWD=", cur_pwd);
		add("OLDPWD", env, number_of_var(*env), tmp);
		g_data.pwd_s = 1;
		free_ptr(&tmp);
		if (!sig)
			free_ptr(&cur_pwd);
	}
}

void	check_delete(char ***env)
{
	int	exist;
	int	env_size;

	g_data.pwd_d = 0;
	g_data.pwd_s = 0;
	exist = check_if_exist_v1("OLDPWD", env);
	env_size = number_of_var(*env);
	if (exist != -1)
	{
		free(*(*env + exist));
		*(*env + exist) = ft_strdup("OLDPWD=");
	}
}
