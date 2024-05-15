#include "../../minishell.h"

char    **ft_strdup_args(char **table)
{
    int     len;
    char    **r_table;

    if (!table)
        return (NULL);
    len = 0;
    while (table[len])
        len++;
    r_table = (char **)malloc(sizeof(char *) * (len + 1));
    if (!r_table)
        return (NULL);
    len = 0;
    while (table[len])
    {
        r_table[len] = ft_strdup(table[len]);
        if (!table[len])
            return (NULL);
        len++;
    }
    r_table[len] = 0;
    return (r_table);
}

static int	ft_strlen_with(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (i);
}



char	*find_var(char **en, char *var)
{
	char	*test_with;
	int		i;

	i = -1;
	test_with = NULL;
	while (en[++i])
	{
		test_with = ft_substr(en[i], 0, ft_strlen_with(en[i], '='));
		if (ft_strlen(var) == ft_strlen(test_with))
		{
			if (ft_strncmp(var, test_with, ft_strlen(var)) == 0)
			{
				free(test_with);
				return (en[i] + (ft_strlen(var) + 1));
			}
		}
		free(test_with);
	}
	return (NULL);
}

char	**herdoc_args(char *cmd_new, t_cmd *cmd)
{
	char	**args;

	args = (char **)malloc(sizeof(char *) * 3);
	args[0] = cmd_new;
	args[1] = ft_strdup(cmd->herdoc);
	args[2] = 0;
	return (args);
}

char	*get_cmd(char *cmd, t_data *data)
{
	char	*tmp;
	char	*command;
	char	**paths;
	int		i;

	i = -1;
	paths = ft_split(find_var(data->env_copy, "PATH"), ':');
	if (cmd == NULL || paths == NULL)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
		{
			free_double_ptr(paths);
			return (command);
		}
		free(command);
	}
	free_double_ptr(paths);
	return (NULL);
}
