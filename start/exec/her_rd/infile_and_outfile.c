#include "../../../minishell.h"

void    handle_in_file(t_cmd *cmd, char *file_name)
{
    if (cmd->in_file > 0)
		close(cmd->in_file);
	cmd->in_file = open(file_name, O_RDONLY, 0644);
	if (cmd->in_file < 0)
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] ", 2);
        ft_putstr_fd(file_name, 2);
        ft_putendl_fd(" No such file or directory", 2);
		g_data.r_error = 1;
		free_cmds();
	}
}

void	handle_out_file(t_cmd *cmd, char *file_name)
{
	if (cmd->out_file > 0)
		close(cmd->out_file);
	cmd->out_file = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (cmd->out_file < 0)
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] ", 2);
        ft_putstr_fd(file_name, 2);
        ft_putendl_fd(" No such file or directory", 2);
		g_data.r_error = 1;
		free_cmds();
	}
}

void	handle_out_file_append(t_cmd *cmd, char *file_name)
{
	if (cmd->out_file > 0)
		close(cmd->out_file);
	cmd->out_file = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (cmd->out_file < 0)
	{
		ft_putstr_fd("[+ \033[31mERROR\033[0m +] ", 2);
        ft_putstr_fd(file_name, 2);
        ft_putendl_fd(" No such file or directory", 2);
		g_data.r_error = 1;
		free_cmds();
	}
}