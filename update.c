/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:31:55 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:31:56 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update(t_NODE *first, size_t number)
{
	t_NODE	*tmp;
	size_t	size;
	size_t	i;
	char	*str;
	char	**ptr_2;

	size = number_of_var(tmp->value->exec_cmd->argv);
	number -= 1;
	ptr_2 = ft_calloc(sizeof(char *), (size + number + 1));
	ft_memcpy(ptr_2, tmp->value->exec_cmd->argv, size * sizeof(char *));
	free(tmp->value->exec_cmd->argv);
	tmp->value->exec_cmd->argv = ptr_2;
	i = 0;
	while (i < number)
	{
		str = ft_strdup(*(first->value->redr_cmd->list_file_name + i + 1));
		*(tmp->value->exec_cmd->argv + size + i) = str;
		i++;
	}
	*(tmp->value->exec_cmd->argv + size + i) = 0;
	free_of_update(first);
}

t_NODE	*create_initialize(t_NODE *node, size_t number)
{
	char	**ptr;
	size_t	i;
	char	*str;
	t_NODE	*exc_cmd;

	ptr = malloc((sizeof(char *)) * (number + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*(node->value->redr_cmd->list_file_name + i + 1))
	{
		str = ft_strdup(*(node->value->redr_cmd->list_file_name + i + 1));
		*(ptr + i) = str;
		i++;
	}
	*(ptr + i) = 0;
	exc_cmd = malloc(sizeof(t_NODE));
	if (!exc_cmd)
	{
		ft_putendl_fd("[+ \033[31mERROR\033[0m +] with malloc()\n", 2);
		return (NULL);
	}
	exc_cmd->type = EXEC;
	exc_cmd->value = initialize_node_exec(ptr);
	return (exc_cmd);
}

void	init_new_command(t_NODE *first, size_t number, t_NODE *tmp)
{
	t_NODE	*exc_cmd;

	exc_cmd = create_initialize(first, number);
	if (!exc_cmd)
		return ;
	tmp = first->next;
	if (tmp)
		tmp->prev = exc_cmd;
	first->next = exc_cmd;
	exc_cmd->prev = first;
	exc_cmd->next = tmp;
}

void	update_one(t_NODE *first, size_t number)
{
	t_NODE	*tmp;
	t_NODE	*exc_cmd;

	tmp = first->prev;
	while (tmp)
	{
		if ((tmp)->type == EXEC || (tmp)->type == PIPE)
			break ;
		tmp = (tmp)->prev;
	}
	if (tmp == NULL)
		init_new_command(first, number, tmp);
	else if ((tmp)->type == PIPE)
		init_new_command(first, number, tmp);
	else if ((tmp)->type == EXEC)
		update(first, number);
}

void	check_redr(t_NODE *first)
{
	t_NODE	*tmp;
	size_t	number;
	int		v;

	if (!first)
		return ;
	v = 1;
	while (first)
	{
		if (first->type == REDR)
		{
			number = number_of_var(first->value->redr_cmd->list_file_name);
			if (number > 1)
				update_one(first, number);
		}
		first = first->next;
	}
}
