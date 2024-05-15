#include "../../minishell.h"

static int in_file(t_cmd *cmd)
{
    if (cmd->in_file > 0)
		return (cmd->in_file);
	else if (cmd->cmd_index != 0)
		return (g_data.pip[cmd->cmd_index - 1][0]);
	return (0);
}

static int      out_file(t_cmd *cmd)
{
    if (cmd->out_file > 0)
		return (cmd->out_file);
	else if (cmd->cmd_index != g_data.n_of_cmd - 1)
		return (g_data.pip[cmd->cmd_index][1]);
	return (1);
}

static void     close_fds(t_cmd *cmd)
{
    int	i;

	i = -1;
	while (++i < (g_data.n_of_cmd - 1))
	{
		if (cmd->cmd_index != i)
			close(g_data.pip[i][1]);
		if (cmd->cmd_index - 1 != i)
			close(g_data.pip[i][0]);
	}
}

char	**no_args(char *cmd_new)
{
	char	**args;

	args = (char **)malloc(sizeof(char *) * 2);
	args[0] = cmd_new;
	args[1] = 0;
	return (args);
}

static char **with_args(char *cmd_new, t_cmd *cmd)
{
    int     i;
    char    **args;

    i = 0;
    while (cmd->args[i])
        i++;
    args = (char **)malloc(sizeof(char *) * (i + 1));
    args[0] = ft_strdup(cmd_new);
    i = 0;
    while (cmd->args[++i])
        args[i] = ft_strdup(cmd->args[i]);
    args[i] = 0;
    return (args);
}

static char     **cmd_args(t_cmd *cmd, t_data *data)
{
    char	*cmd_new;
	int		i;

	i = 0;

	if (!cmd->cmd || *(cmd->cmd) == '\0')
		return (NULL);
	cmd_new = get_cmd(cmd->cmd, data);
	if (!cmd_new)
		return (NULL);
    if (cmd->args[1])
        return (with_args(cmd_new, cmd));
    if (cmd->herdoc_boolean && !cmd->args[1])
        return (herdoc_args(cmd_new, cmd));
	if (!cmd->args[1])
		return (no_args(cmd_new));
	return (NULL);
}

int check_builtin(t_cmd *cmd, t_data *data)
{
	if (!ft_strncmp(cmd->cmd, "env", 4))
		return (ft_env(cmd));
	else if (!ft_strncmp(cmd->cmd, "pwd", 4))
		return (ft_pwd(cmd));
	else if (!ft_strncmp(cmd->cmd, "echo", 5))
		return (echo(cmd));
	else if (!ft_strncmp(cmd->cmd, "exit", 5))
		return (ft_exit(cmd));
	else if (!ft_strncmp(cmd->cmd, "export", 7))
		return (export(cmd));
	else if (!ft_strncmp(cmd->cmd, "unset", 6))
		return (unset(cmd));
	else if (!ft_strncmp(cmd->cmd, "cd", 3))
		return (ft_cd(cmd));
	return (-10);
}

void check_cmds(t_cmd *cmd)
{
	DIR	*folder;
	int	fd;

	fd = open(cmd->cmd, O_WRONLY);
	folder = opendir(cmd->cmd);
	if (fd == -1 && folder != NULL)
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		exit (126);
	}
}

void	print_error_msg(t_cmd *cmd, int n_e, char *msg)
{
	ft_putstr_fd("[+ \033[31mERROR\033[0m +] ", 2);
	ft_putstr_fd(cmd->cmd, 2);
	ft_putendl_fd(msg , 2);
	exit (n_e);
}

void	do_execute_cmd(char **new_args, t_data *data)
{
	if (execve(new_args[0], new_args, data->env_copy) == -1)
    {
		ft_putstr_fd("[+ \033[31mERROR\033[0m +]", 2);
		perror(" ");
		exit (errno);
	}
}

void	check_error(t_cmd *cmd)
{
	int	fd;
	DIR	*dir;

	fd = open(cmd->cmd, O_WRONLY);
	dir = opendir(cmd->cmd);
	if (ft_strchr(cmd->cmd, '/') == NULL)
		print_error_msg(cmd, 127, " command not found");
    else if (fd < 0 && dir != NULL)
		print_error_msg(cmd, 126, " is a directory");
	else if (fd < 0 && dir == NULL)
		print_error_msg(cmd, 126, " No such file or directory");
	else if (fd != -1 && dir == NULL)
		print_error_msg(cmd, 126, " Permission denied");
	if (dir)
		closedir(dir);
	if (fd != -1)
		close(fd);
	exit (127);
}

void	execute_cmd(t_cmd *cmd, t_data *data)
{
    char	**new_args;
	int		return_value;

	return_value = check_builtin(cmd, data);
	if (return_value != -10)
	 	exit(return_value);
	else
	{
		new_args = cmd_args(cmd, data);
		if (new_args == NULL)
			check_error(cmd);
		check_cmds(cmd);
        do_execute_cmd(new_args, data);
	}
}

void	fork_for_cmds(t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		ft_putendl_fd("[+ \033[31mERROR\033[0m +] FORK()\n", 2);
		g_data.r_error = 11;
		return ;
	}
	if (cmd->pid == 0)
	{
		close_fds(cmd);
		dup2(in_file(cmd), 0);
		dup2(out_file(cmd), 1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execute_cmd(cmd, &g_data);
	}
}