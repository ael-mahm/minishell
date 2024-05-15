/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:33:47 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:33:49 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_NODE	*first_node(t_NODE *top)
{
	if (!top)
		return (NULL);
	while (top->prev)
		top = top->prev;
	return (top);
}

t_NODE	*do_create_pipe(t_PIPE_CMD *tmp)
{
	t_NODE		*exc_cmd;
	t_value		*ptr;

	ptr = malloc(sizeof(t_value));
	if (!ptr)
	{
		free(tmp);
		return (NULL);
	}
	ptr->pipe_cmd = tmp;
	exc_cmd = malloc(sizeof(t_NODE));
	if (!exc_cmd)
	{
		free(tmp);
		free(ptr);
		return (NULL);
	}
	exc_cmd->value = ptr;
	exc_cmd->next = NULL;
	exc_cmd->type = PIPE;
	return (exc_cmd);
}

t_NODE	*create_pipe(char **str)
{
	t_PIPE_CMD	*tmp;
	char		*tmp2;

	tmp2 = *str;
	while ((*tmp2 == ' ' || *tmp2 == '\t') && *tmp2)
		tmp2++;
	if (*tmp2 == '|')
		tmp2++;
	*str = tmp2;
	tmp = malloc(sizeof(t_PIPE_CMD));
	if (!tmp)
		return (NULL);
	tmp->arg = strdup("|");
	return (do_create_pipe(tmp));
}

t_value	*initialize_node_exec(char **ptr)
{
	t_EXEC_CMD	*tmp;
	t_value		*data_cmd;

	tmp = malloc(sizeof(t_EXEC_CMD));
	if (!tmp)
		return (NULL);
	tmp->argv = ptr;
	data_cmd = malloc(sizeof(t_value));
	if (!data_cmd)
	{
		free(tmp);
		return (NULL);
	}
	data_cmd->exec_cmd = tmp;
	return (data_cmd);
}

t_NODE	*create_exec(char **str, char c, char **env)
{
	char	**ptr;
	t_NODE	*exc_cmd;

	ptr = NULL;
	ptr = get_files(str, c, env);
	if (!ptr)
		return (NULL);
	exc_cmd = malloc(sizeof(t_NODE));
	if (!exc_cmd)
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] with malloc()\n", 2);
		g_data.r_error = 1;
		return (NULL);
	}
	exc_cmd->next = NULL;
	exc_cmd->type = EXEC;
	exc_cmd->value = initialize_node_exec(ptr);
	if (!exc_cmd->value)
		free_double_ptr(ptr);
	return (exc_cmd);
}
