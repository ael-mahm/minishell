/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:32:06 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:32:07 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_ptr(char **ptr)
{
	size_t	i;

	if (!ptr)
		return ;
	i = 0;
	while (*(ptr + i))
	{
		free(*(ptr + i));
		i++;
	}
	free(ptr);
}

char	*read_line(void)
{
	char	*buffer;

	buffer = NULL;
	g_data.sig_int.sa_handler = &handler;
	sigaction(SIGINT, &g_data.sig_int, NULL);
	buffer = readline("[+ SHELL +] ");
	if (!buffer)
		return (NULL);
	if (*buffer)
		add_history(buffer);
	return (buffer);
}

int	print_error_qoutes(int time)
{
	if (time == 1)
	{
		ft_putendl_fd("[+ \033[31mERROR\033[0m +] check quotes!", 2);
		g_data.r_error = 1;
		return (1);
	}
	return (0);
}

int	check_quotes(char *buffer)
{
	char	tmp;
	int		time;

	time = 0;
	while (*buffer)
	{
		while ((*buffer != '\"' && *buffer != '\'') && *buffer)
			buffer++;
		if (*buffer)
		{
			tmp = *buffer;
			time = 1;
			buffer++;
		}
		while (*buffer && (*buffer != tmp))
			buffer++;
		if (*buffer)
		{
			time = 0;
			buffer++;
		}
	}
	return (print_error_qoutes(time));
}

void	handler2(int sig)
{
	(void)sig;
	write (1, "\n", 1);
}
