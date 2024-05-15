/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redr_utlis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:31:45 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:31:47 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str, char c)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	g_data.r_error = 1;
}

int	checkone(char **str)
{
	if (peek(*str) == '|' || peek(*str) == '<' || peek(*str) == '>')
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] ", 2);
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(peek(*str), 2);
		ft_putstr_fd("'\n", 2);
		g_data.r_error = 2;
		return (1);
	}
	return (0);
}

int	check_err(char *tmp_str, char **str)
{
	if (*tmp_str == '>')
	{
		ft_putendl_fd("[+ \033[31mERROR\033[0m +] ", 2);
		ft_putendl_fd("syntax error near unexpected token `>'", 2);
		g_data.r_error = 2;
		return (1);
	}
	if (peek(*str) == '|' || peek(*str) == '<' || peek(*str) == '>')
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] ", 2);
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(peek(*str), 2);
		ft_putstr_fd("'\n", 2);
		g_data.r_error = 2;
		return (1);
	}
	return (0);
}

int	check_errors_rd4(char **str)
{
	if (**str == '<')
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] ", 2);
		ft_putendl_fd("syntax error near unexpected token `<'", 2);
		g_data.r_error = 2;
		return (1);
	}
	if (peek(*str) == '|' || peek(*str) == '<' || peek(*str) == '>')
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] ", 2);
		ft_putstr_fd("syntax error near unexpected token `", 2);
		g_data.r_error = 2;
		ft_putchar_fd(peek(*str), 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

void	free_ptr(char **ptr)
{
	if (!ptr)
		return ;
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}
