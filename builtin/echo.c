/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:27:00 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:27:05 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checker_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

void	check_args(int *i, int *v, t_cmd *cmd)
{
	if (cmd->args[*i])
	{
		if (!ft_strncmp(cmd->args[*i], "-n", 2))
		{
			while ((cmd->args[*i] && !ft_strncmp(cmd->args[*i], "-n", 3)) \
			|| (checker_n(cmd->args[*i])))
			{
				*i = *i + 1;
				*v = 1;
				if (!cmd->args[*i])
					break ;
			}
		}
	}
}

void	print_args(t_cmd *cmd, int *i, int fd, int v)
{
	if (cmd->args + *i)
	{
		while (cmd->args[*i])
		{
			ft_putstr_fd(cmd->args[*i], fd);
			*i = *i + 1;
			if (cmd->args[*i])
				ft_putstr_fd(" ", fd);
		}
	}
	if (!v)
		write(fd, "\n", 1);
	if (cmd->out_file > 0)
		close (cmd->out_file);
}

int	echo(t_cmd *cmd)
{
	int	i;
	int	v;
	int	fd;

	fd = 1;
	if (!cmd)
	{
		g_data.r_error = 1;
		return (1);
	}
	if (cmd->out_file > 0)
		fd = cmd->out_file;
	i = 1;
	v = 0;
	if (cmd->args[1] == NULL)
	{
		write(fd, "\n", 1);
		g_data.r_error = 0;
		return (1);
	}
	check_args(&i, &v, cmd);
	print_args(cmd, &i, fd, v);
	g_data.r_error = 0;
	return (g_data.r_error);
}
