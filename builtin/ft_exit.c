/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:28:49 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:28:50 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(void)
{
	free_cmds();
	free_double_ptr(g_data.env_copy);
	free_node(g_data.parsed_data);
}

int	is_all_number(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	checkexit(t_cmd *cmd)
{
	if (!cmd->args[1])
	{
		ft_putendl_fd("exit", 1);
		free_all();
		exit(0);
	}
}

void	checkexittwo(t_cmd *cmd)
{
	if (is_all_number(cmd->args[1]))
	{
		ft_putstr_fd("exit\n[+ \033[31mERROR\033[0m +] :exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_all();
		exit (255);
	}
}

int	ft_exit(t_cmd *cmd)
{
	int	exit_code;

	checkexit(cmd);
	if (cmd->args[1])
	{
		checkexittwo(cmd);
		if (cmd->args[2])
		{
			ft_putendl_fd("exit", 2);
			ft_putstr_fd("[+ \033[31mERROR\033[0m +] ", 2);
			ft_putendl_fd("exit: too many arguments", 2);
			g_data.r_error = 1;
			return (g_data.r_error);
		}
		ft_putstr_fd("exit\n", 1);
		exit_code = ft_atoi(cmd->args[1]);
		free_all();
		exit (exit_code);
	}
	return (1);
}
