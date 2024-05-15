/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:30:34 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:30:35 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	(void)sig;
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_data.r_error = 130;
}

void	main_init(char **env)
{
	char	**dup_env;

	dup_env = NULL;
	dup_env = duplicate_env(env);
	if (!dup_env)
	{
		ft_putendl_fd("[+ \033[31mERROR\033[0m +] with env!", 2);
		exit (1);
	}
	g_data.n_of_cmd = 0;
	g_data.n_of_cmd_old = 0;
	g_data.env_copy = dup_env;
	g_data.pwd_s = 0;
	g_data.pwd_d = 1;
}

void	ft_read_line(t_NODE **top, char **input)
{
	*top = NULL;
	*input = read_line();
	if (*input == NULL)
	{
		free_double_ptr(g_data.env_copy);
		ft_putendl_fd("exit", 1);
		exit (0);
	}	
}

void	while_loop(void)
{
	char	*input;
	char	*t;
	t_NODE	*top;
	t_NODE	*tmp;

	ft_read_line(&top, &input);
	g_data.sig_int.sa_handler = &handler2;
	sigaction(SIGINT, &g_data.sig_int, NULL);
	if (input)
	{
		t = input;
		if (!check_quotes(t))
		{
			top = parsing(&input, g_data.env_copy);
			tmp = first_node(top);
			check_redr(tmp);
			tmp = first_node(top);
			g_data.parsed_data = tmp;
			execution();
			free_node(tmp);
			top = NULL;
		}
		free(t);
	}
}

int	main(int argc, char const *argv[], char **env)
{
	struct sigaction	sig_quit;

	sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_flags = SA_RESTART;
	g_data.sig_int.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_quit, NULL);
	main_init(env);
	while (true)
		while_loop();
	return (0);
}
