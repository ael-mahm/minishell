/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utlis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:27:21 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:27:23 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_declare_x(t_cmd *cmd, char **str)
{
	size_t	i;
	char	**split;
	char	*tmp;
	int		fd;

	i = 0;
	fd = 1;
	if (cmd->out_file > 0)
		fd = cmd->out_file;
	while (*(str + i))
	{
		ft_putstr_fd("declare -x ", fd);
		split = ft_split(*(str + i), '=');
		if (!split)
			return ;
		tmp = ft_strchr(*(str + i), '=');
		ft_putstr_fd(*(split + 0), fd);
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(tmp + 1, fd);
		ft_putendl_fd("\"", fd);
		i++;
		if (split)
			free_double_ptr(split);
	}
}

size_t	number_of_var(char **env)
{
	size_t	i;

	i = 0;
	while (*(env + i))
		i++;
	return (i);
}

int	check_valid_name(char *str)
{
	size_t	i;

	if ((*str < 'A' || *str > 'Z') && (*str < 'a' || *str > 'z') && *str != '_')
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	i = 1;
	while (*(str + i))
	{
		if ((*(str + i) < 'A' || *(str + i) > 'Z') \
		&& (*(str + i) < 'a' || *(str + i) > 'z') \
		&& (*(str + i) < '0' || *(str + i) > '9') && *(str + i) != '_')
		{
			ft_putstr_fd("[+ \033[31mERROR\033[0m +] `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
