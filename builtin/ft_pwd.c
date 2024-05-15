/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:27:58 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:27:59 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*tmp;
	int		fd;

	fd = 1;
	if (!cmd)
	{
		g_data.r_error = 1;
		return (1);
	}
	if (cmd->out_file > 0)
		fd = cmd->out_file;
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		ft_putendl_fd("[+ \033[31mERROR\033[0m +] PWD()", fd);
		g_data.r_error = 1;
		return (1);
	}
	else
		ft_putendl_fd(tmp, fd);
	free_ptr(&tmp);
	g_data.r_error = 0;
	if (cmd->out_file > 0)
		close (cmd->out_file);
	return (g_data.r_error);
}
