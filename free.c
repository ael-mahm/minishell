/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:31:03 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:31:04 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_of_update(t_NODE *node)
{
	size_t	i;

	i = 1;
	while (*(node->value->redr_cmd->list_file_name + i))
	{
		free(*(node->value->redr_cmd->list_file_name + i));
		*(node->value->redr_cmd->list_file_name + i) = NULL;
		i++;
	}
}

void	free_exec(t_NODE *first)
{
	free_double_ptr(first->value->exec_cmd->argv);
	free((first->value->exec_cmd));
	free((first->value));
	free(first);
}

void	free_pipe(t_NODE *first)
{
	free_ptr(&(first->value->pipe_cmd->arg));
	free((first->value->pipe_cmd));
	free((first->value));
	free(first);
}

void	free_redr(t_NODE *first)
{
	free_double_ptr(first->value->redr_cmd->list_file_name);
	free((first->value->redr_cmd));
	free((first->value));
	free(first);
}

void	free_node(t_NODE *first)
{
	t_NODE	*tmp;

	tmp = first;
	while (first)
	{
		tmp = first->next;
		if (first->type == EXEC)
			free_exec(first);
		else if (first->type == PIPE)
			free_pipe(first);
		else if (first->type == REDR)
			free_redr(first);
		first = tmp;
	}
}
