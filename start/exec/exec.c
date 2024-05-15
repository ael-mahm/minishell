#include "../../minishell.h"

static void     free_table_of_pipe(void)
{
    int	i;

	i = -1;
	if (g_data.n_of_cmd_old != 0)
	{
		while (++i < (g_data.n_of_cmd_old - 1))
			free(g_data.pip[i]);
		free(g_data.pip);
	}
	g_data.n_of_cmd_old = 0;
}

static void    init_table_pipe(void)
{
    int	index;

	index = -1;
	free_table_of_pipe();
	g_data.pip = malloc(sizeof(int *) * (g_data.n_of_cmd - 1));
    if (!g_data.pip)
        return ;
	while (++index < (g_data.n_of_cmd - 1))
	{
        g_data.pip[index] = malloc(sizeof(int) * 2);
        if (!g_data.pip[index])
            return ;
    }
    g_data.n_of_cmd_old = g_data.n_of_cmd;
}

static int     make_pipes(void)
{
    int	i;

	i = -1;
	while (++i < (g_data.n_of_cmd - 1))
	{
		if (pipe(g_data.pip[i]) == -1)
			return (1);
	}
	return (0);
}

void	close_fds_main(void)
{
	int	i;

	i = -1;
	while (++i < (g_data.n_of_cmd - 1))
	{
		close(g_data.pip[i][1]);
		close(g_data.pip[i][0]);
	}
}

void	wait_pids(void)
{
	t_cmd		*wai_cmd;
	int			r_return;

	wai_cmd = g_data.cmds;
	close_fds_main();
	while (wai_cmd)
	{
		if (wai_cmd->in_file > 0)
			close(wai_cmd->in_file);
		if (wai_cmd->out_file > 0)
			close(wai_cmd->out_file);
		waitpid(wai_cmd->pid, &r_return, 0);
		if (WIFEXITED(r_return))
			g_data.r_error = WEXITSTATUS(r_return);
		else
			g_data.r_error = 130;
		wai_cmd = wai_cmd->next;
	}
}

int    start_exec_cmds()
{
    t_cmd   *all_cmds;
	int i;
	int v;
    all_cmds = g_data.cmds;
	v = 0;
    if(g_data.n_of_cmd == 1)
	{
		if (!ft_strncmp(all_cmds->cmd, "env", 4))
			return (ft_env(all_cmds));
		else if (!ft_strncmp(all_cmds->cmd, "pwd", 4))
			return (ft_pwd(all_cmds));
		else if (!ft_strncmp(all_cmds->cmd, "echo", 5))
			return (echo(all_cmds));
		else if (!ft_strncmp(all_cmds->cmd, "exit", 5))
			return (ft_exit(all_cmds));
		else if (!ft_strncmp(all_cmds->cmd, "export", 7))
			return (export(all_cmds));
		else if (!ft_strncmp(all_cmds->cmd, "unset", 6))
			return (unset(all_cmds));
		else if (!ft_strncmp(all_cmds->cmd, "cd", 3))
			return (ft_cd(all_cmds));
	}
		if (all_cmds)
		{
			init_table_pipe();
			if (make_pipes())
				return (1);
			while (all_cmds)
			{
				fork_for_cmds(all_cmds);
				all_cmds = all_cmds->next;
			}
			wait_pids();
		}
	
	
}

void execution(void)
{
    if (g_data.parsed_data)
    {
        convert_data_parser();
        if (g_data.cmds == NULL)
            return ;
        start_exec_cmds();
        free_cmds();
    }
}