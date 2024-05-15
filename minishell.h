/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:33:03 by ael-mahm          #+#    #+#             */
/*   Updated: 2022/11/30 12:33:07 by ael-mahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef enum e_type
{
	EXEC = 0,
	PIPE = 1,
	REDR = 2
}	t_type;

typedef struct s_string
{
	char	*new_string;
	char	*tmp;
}	t_string;

typedef struct s_exec
{
	char	**argv;
}	t_EXEC_CMD;

typedef struct s_pipe
{
	char	*arg;
}	t_PIPE_CMD;

typedef struct s_redr
{
	char	**list_file_name;
	char	type_redr;
	int		mode;
	int		fd;
}	t_REDR_CMD;

typedef union u_value
{
	t_EXEC_CMD	*exec_cmd;
	t_PIPE_CMD	*pipe_cmd;
	t_REDR_CMD	*redr_cmd;
}	t_value;

typedef struct s_NODE
{
	t_type			type;
	t_value			*value;
	struct s_NODE	*prev;
	struct s_NODE	*next;
}	t_NODE;

typedef struct s_n
{
	int	i;
	int	j;
}	t_n;

typedef struct s_cmd
{
	int				cmd_index;
	char			**args;
	char			*cmd;
	int				herdoc_boolean;
	char			*herdoc;
	int				in_file;
	int				out_file;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	int					r_error;
	struct sigaction	sig_int;
	int					**pip;
	char				**env_copy;
	int					n_of_cmd;
	int					n_of_cmd_old;
	t_NODE				*parsed_data;
	t_cmd				*cmds;
	int					pwd_s;
	int					pwd_d;
}	t_data;

t_data					g_data;

void	init_signal(void);
void	check_built_in(t_NODE *top, char ***dup_env, t_data *arg);
void	fork_for_cmds(t_cmd *cmd);
char	**ft_strdup_args(char **table);
void	convert_data_parser(void);
void	execution(void);
void	push_back_cmd(t_cmd **head_cmd, t_cmd *new);
t_cmd	*init_cmd_node(void);
void	free_cmds(void);
void	handle_in_file(t_cmd *cmd, char *file_name);
void	handle_out_file(t_cmd *cmd, char *file_name);
void	handle_out_file_append(t_cmd *cmd, char *file_name);
void	handle_herdoc(t_cmd *cmd, char *end_of_file);
char	*get_cmd(char *cmd, t_data *data);
char	**herdoc_args(char *cmd_new, t_cmd *cmd);
char	*find_var(char **en, char *var);
int		echo(t_cmd *cmd);
void	print_declare_x(t_cmd *cmd, char **str);
size_t	number_of_var(char **env);
int		check_valid_name(char *str);
int		check_valid_name_v1(char *str);
int		check_if_exist(char *str, char ***env);
int		check_and_print(t_cmd *cmd, char ***env, size_t *argv_size);
int		export(t_cmd *cmd);
void	add(char *tmp, char ***env, int env_size, char *str);
char	*get_value_of_env(char ***env, char *str);
int		exec_chdir(char ***env, char *path, int v);
int		exec_home(char ***env);
int		exec_one(char ***env);
int		check_errors(t_cmd *cmd);
int		check_e(char ***env, t_cmd *cmd);
int		ft_cd(t_cmd *cmd);
int		ft_env(t_cmd *cmd);
int		ft_exit(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd);
int		check_if_exist_v1(char *str, char ***env);
int		check_and_delete(t_cmd *cmd, char ***env, size_t argv_size);
int		unset(t_cmd *cmd);
t_NODE	*first_node(t_NODE *top);
t_NODE	*do_create_pipe(t_PIPE_CMD *tmp);
t_NODE	*create_pipe(char **str);
t_value	*initialize_node_exec(char **ptr);
t_NODE	*create_exec(char **str, char c, char **env);
char	**count_and_alloc(char **env);
char	**duplicate_env(char **env);
void	free_of_update(t_NODE *node);
void	free_exec(t_NODE *first);
void	free_pipe(t_NODE *first);
void	free_redr(t_NODE *first);
void	free_node(t_NODE *first);
int		get_len_of_string(char **str);
char	*get_str(char **str, int size);
int		get_len_q_v4(char *start);
char	*get_string_q_v4(char **start, int size);
void	value_of_single_var(char **start);
int		value_of_var(char **start, char **env);
void	func_get_value_of_var(char **e, char **s, int *l, char **v);
void	get_value_of_r_error(char **value_var, int *len_string, char **start);
void	increment(char **start, int *i, int *j);
int		get_len_q_v1_new(char *start, char *end, char **env);
int		get_len_q_v1_new_2(char *start, char **env);
void	get_value_of_r_error_2(char **value_var, int *len_string, char **start);
void	func_1_get_var(char **e, int *l, char **v, char **m);
void	copy_to_tmp_and_free(int *i, char **v, char *t, int l);
void	check_and_set(char **env, char **m_start, t_n *n, char *tmp);
char	*get_string_q_v1_and_move_2(char **start, int size, char **env);
char	*get_string_q_v1_and_move(char **s, char *e, int si, char **el);
int		get_len_v_3(char *start, char *end);
int		get_len_v_2(char *start, char *end);
char	*get_string_move_start_2(char **start, char *end, int size);
char	*allocate_and_copy(int i, char *tmp);
char	*handle_single_string(char **str, char c, char **env);
char	*get_name_variable(char *tmp, int i);
int		get_lenght_variable(char *tmp);
char	*get_value_variable(char *var_name, char **env);
void	handle_single_var(int *i, int *l, char ***va, int *s);
int		handle_var_name(char *tmp, int *i, int *size, char ***variables);
void	do_get_and_replace(char ***variables, int *number, t_string *s, t_n *n);
void	get_and_replace(int len_malloc, char ***variables, t_string *s);
int		do_handle_qoutes_string(char **str, char *t, char ***v, int *s);
char	*handler_space(char **str, char **tmp);
char	*handle_qoutes_string(char **str, char c, char **env);
void	free_double_ptr(char **ptr);
void	handler(int sig);
void	add_node(t_NODE *cmd, t_NODE **top);
void	handler2(int sig);
int		print_error_qoutes(int time);
int		check_quotes(char *buffer);
void	print_error(char *str, char c);
int		checkone(char **str);
t_NODE	*do_create_redr_node(t_REDR_CMD *tmp);
t_NODE	*create_redr_node(char **ptr_2, char type_redr);
int		check_err(char *tmp_str, char **str);
t_NODE	*create_redr_3(char **str, char **env);
t_NODE	*create_redr_2(char **str, char **env);
t_NODE	*create_redr(char **str, char **env);
int		check_errors_rd4(char **str);
t_NODE	*create_redr_4(char **str, char **env);
void	free_ptr(char **ptr);
void	func1(char *tmp, int *i, int *size, char **env);
int		get_size_of_line(char *tmp, char **env);
void	func2(char *tmp, t_n *n, char *return_value, char **env);
char	*get_line(char *tmp, char **env);
char	peek(char *str);
void	scanner_qoutes(char **es);
void	scanner_single(char **es);
void	get_end(char **es);
int		do_scanner(char **tmp, char **e);
int		scanner(char **string, char **s, char **e);
char	**ft_realloc(char **ptr, int size);
char	*name_and_value(char **str, char **env);
char	*get_new_str(char **str, char **env);
char	*check_and_get_new_str(char **str, char **env);
int		ft_isspace(char tmp);
char	*function_three(char **str, char **env, char c);
char	*name_and_value_v(char **str, char **env, char **start);
char	*get_value_of_exit(void);
char	*get_new_str_v(char **str, char **env, char **start);
char	*fn_check_exec(char **str, int *v, char *end, char **start);
int		set_v(char *start, int *v);
void	func_space(char **str, char **start, char **end);
char	*function_four(char **str, char **env);
char	*fn_check_exec_v(char **str, int *v, char *end, char **start);
char	*function_five(char **str, char **env);
char	**get_files(char **str, char c, char **env);
void	check_v(void);
void	check_delete(char ***env);
void	change_old_pwd(char **value, char *pwwd, char ***env);
int		ft_cd_sys(char *path, char **pwwd);
int		print_error_qoutes(int time);
int		check_quotes(char *buffer);
char	*read_line(void);
t_NODE	*check_pipe(t_NODE *top, char **string);
t_NODE	*check_c(char **string, char **env, char c, t_NODE *top);
t_NODE	*parsing(char **string, char **env);
void	update(t_NODE *node, size_t number);
t_NODE	*create_initialize(t_NODE *node, size_t number);
void	update_and_create(t_NODE *node, size_t number);
void	check_redr(t_NODE *first);
void	init_numbers(int *number, t_n *n);
void	move_tmp(t_NODE	**tmp, int number, t_NODE *node);
void	while_loop_tmp(t_NODE *tmp, t_NODE *first, int number);
void	free_all(void);

#endif
