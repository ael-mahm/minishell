/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:34:25 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:34:26 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node(t_NODE *cmd, t_NODE **top)
{
	if (!cmd || !top)
		return ;
	cmd->prev = *top;
	cmd->next = NULL;
	if (*top)
		(*top)->next = cmd;
	*top = cmd;
}

void	print_pipe_error(void)
{
	ft_putstr_fd("[+ \033[31mERROR\033[0m +] ", 2);
	ft_putendl_fd("syntax error near unexpected token `|'", 2);
	g_data.r_error = 2;
}

t_NODE	*check_pipe(t_NODE *top, char **string)
{
	t_NODE	*cmd;
	char	c;

	if (top == NULL)
	{
		print_pipe_error();
		return (NULL);
	}
	cmd = create_pipe(string);
	if (!cmd)
	{
		print_error("[+ \033[31mERROR\033[0m +] with malloc()", '|');
		g_data.r_error = 1;
		return (NULL);
	}
	c = peek(*string);
	if (c == '|')
	{
		print_pipe_error();
		free_node(cmd);
		return (NULL);
	}
	cmd->type = PIPE;
	return (cmd);
}

t_NODE	*check_c(char **string, char **env, char c, t_NODE *top)
{
	t_NODE	*cmd;
	t_NODE	*tmp;

	cmd = NULL;
	if (c == '|')
		cmd = check_pipe(top, string);
	else if (c == '<')
		cmd = create_redr(string, env);
	else if (c == '>')
		cmd = create_redr_2(string, env);
	else
		cmd = create_exec(string, c, env);
	if (cmd == NULL)
	{
		tmp = first_node(top);
		free_node(tmp);
		return (NULL);
	}
	return (cmd);
}

t_NODE	*parsing(char **string, char **env)
{
	char	c;
	t_NODE	*cmd;
	t_NODE	*top;
	t_NODE	*tmp;

	top = NULL;
	c = peek(*string);
	while (c != '\0')
	{
		cmd = check_c(string, env, c, top);
		if (cmd == NULL)
			return (NULL);
		add_node(cmd, &top);
		c = peek(*string);
	}
	if (!top)
		return (NULL);
	if (top->type == PIPE)
	{
		print_error("[+ \033[31mERROR\033[0m +] Command not found after `", '|');
		tmp = first_node(top);
		free_node(tmp);
		return (NULL);
	}
	return (top);
}
