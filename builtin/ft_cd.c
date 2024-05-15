/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:28:21 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:28:23 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_pwd(char *path, char ***env)
{
	char	*cur_pwd;
	char	*tmp;

	g_data.pwd_d = 1;
	cur_pwd = getcwd(NULL, 0);
	if (!cur_pwd)
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] cd: ", 2);
		perror(path);
		g_data.r_error = 1;
		return (errno);
	}
	tmp = ft_strjoin("PWD=", cur_pwd);
	add("PWD", env, number_of_var(*env), tmp);
	free_ptr(&cur_pwd);
	free_ptr(&tmp);
	return (0);
}

int	exec_chdir(char ***env, char *path, int v)
{
	char	*value;
	char	*pwwd;

	if (ft_cd_sys(path, &pwwd) != 0)
		return (1);
	value = get_value_of_env(&g_data.env_copy, "PWD");
	if (value || g_data.pwd_d == 0)
		change_old_pwd(&value, pwwd, env);
	else
		check_delete(env);
	free_ptr(&value);
	free_ptr(&pwwd);
	value = get_value_of_env(&g_data.env_copy, "PWD");
	if (value)
	{
		if (add_pwd(path, env))
		{
			free_ptr(&value);
			return (1);
		}
	}
	free_ptr(&value);
	if (v)
		check_v();
	return (0);
}

int	exec_home(char ***env)
{
	char	*home;
	int		r_value;

	r_value = 0;
	home = get_value_of_env(env, "HOME");
	if (!home)
	{
		g_data.r_error = 1;
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] cd: HOME not set\n", 2);
		return (1);
	}
	else if (*home == '\0')
	{
		free(home);
		home = getcwd(NULL, 0);
		r_value = exec_chdir(env, home, 0);
	}
	else if (*home != '\0')
		r_value = exec_chdir(env, home, 0);
	free(home);
	return (r_value);
}

int	exec_one(char ***env)
{
	char	*old_pwd_1;
	int		r_value;

	r_value = 0;
	old_pwd_1 = get_value_of_env(env, "OLDPWD");
	if (!old_pwd_1)
	{
		g_data.r_error = 1;
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (*old_pwd_1 == '\0')
	{
		ft_putstr_fd("\n", 1);
		return (1);
	}
	else
		r_value = exec_chdir(env, old_pwd_1, 1);
	free(old_pwd_1);
	return (r_value);
}

int	ft_cd(t_cmd *cmd)
{
	int	return_value;

	return_value = check_e(&g_data.env_copy, cmd);
	if (return_value != 0)
		return (1);
	return_value = 1;
	if (*(cmd->args + 1) == NULL)
		return_value = exec_home(&g_data.env_copy);
	else if (ft_strncmp(*((cmd->args + 1)), "-", 2) == 0)
		return_value = exec_one(&g_data.env_copy);
	else
		return_value = exec_chdir(&g_data.env_copy, *(cmd->args + 1), 0);
	return (g_data.r_error);
}
