#include "../../minishell.h"

t_cmd   *init_cmd_node(void)
{
    t_cmd *cmd_node = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd_node)
        return (NULL);
    cmd_node->cmd_index = 0;
    cmd_node->cmd = NULL;
    cmd_node->in_file = 0;
    cmd_node->herdoc_boolean = 0;
    cmd_node->herdoc = NULL;
	cmd_node->out_file = 0;
	cmd_node->args = NULL;
	cmd_node->next = NULL;
    return (cmd_node);
}

void    push_back_cmd(t_cmd **head_cmd, t_cmd *new)
{
    t_cmd   *head;

    head = *head_cmd;
    if (*head_cmd == NULL)
        *head_cmd = new;
    else
    {
        while (head->next != NULL)
            head = head->next;
        head->next = new;
    }
}

static void        free_cmds_content(void)
{
    t_cmd   *cmds;

    cmds = g_data.cmds;
    while (cmds != NULL)
    {
        if (cmds->cmd)
            free (cmds->cmd);
        if (cmds->args)
            free_double_ptr(cmds->args);
        if (cmds->herdoc_boolean)
            free (cmds->herdoc);
        cmds = cmds->next;
    }
}

void        free_cmds(void)
{
    t_cmd   *head;
    t_cmd   *head_tmp;

    head = g_data.cmds;
    if (head)
    {
        free_cmds_content();
        while (head)
        {
            head_tmp = head;
            head = head->next;
            head_tmp->next = NULL;
            free (head_tmp);
        }
        free (head);
        g_data.cmds = NULL;
    }
}