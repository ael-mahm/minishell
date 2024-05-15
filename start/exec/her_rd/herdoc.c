#include "../../../minishell.h"


static char	*name_herdoc_file(t_cmd *cmd)
{
	char	*name_file;
	char	*number_of_file;

	number_of_file = ft_itoa(cmd->cmd_index);
	if (!number_of_file)
		return (NULL);
	name_file = ft_strjoin("/tmp/env_", number_of_file);
	free(number_of_file);
	if (!name_file)
		return (NULL);
	return (name_file);
}

static void stock_line_in(t_cmd *cmd, char *eof, char *name_file)
{
    int		fd;
	char	*line;
	char	*line_env;

	line_env = NULL;
	fd = open(name_file, O_TRUNC | O_CREAT | O_RDWR, 0666);
	if (fd < 0)
	{
		free(cmd->herdoc);
		return ;
	}
	while (1)
	{
		line = readline("[+ HEREDOC +] ");
		if (line == NULL || (ft_strncmp(eof, line, ft_strlen(line)) == 0))
		{
			close(fd);
			exit(0);
		}
		else
		{
			line_env = get_line(line, g_data.env_copy);
			ft_putendl_fd(line_env, fd);
			free_ptr (&line_env);
			free_ptr (&line);
		}
	}
}

void    handle_herdoc(t_cmd *cmd, char *end_of_file)
{
    int		pid;
	char	*name_file;

    if (cmd->herdoc_boolean)
        free (cmd->herdoc);
    name_file = name_herdoc_file(cmd);
    if (!name_file)
        return ;
    cmd->herdoc_boolean = 1;
    cmd->herdoc = name_file;
    pid = fork();
    if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		stock_line_in(cmd, end_of_file, name_file);
	}
	else
		waitpid(pid,NULL,0);
}