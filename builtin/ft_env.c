/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:27:48 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:27:51 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_cmd *cmd)
{
	int		i;
	int		fd;
	char	**table;

	fd = 1;
	table = g_data.env_copy;
	if (!table || !cmd)
	{
		g_data.r_error = 1;
		return (1);
	}
	if (cmd->out_file > 0)
		fd = cmd->out_file;
	i = 0;
	while (table[i])
	{
		ft_putendl_fd(table[i], fd);
		i++;
	}
	g_data.r_error = 0;
	if (cmd->out_file > 0)
		close (cmd->out_file);
	return (g_data.r_error);
}
