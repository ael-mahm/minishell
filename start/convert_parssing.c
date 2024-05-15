#include "../minishell.h"

void    convert_data_parser(void)
{
    t_cmd   *new_cmd;
    int         i = 1;
    t_NODE *head_parser;

    head_parser = g_data.parsed_data;
    if (head_parser != NULL)
    {
        new_cmd = init_cmd_node();
        push_back_cmd(&g_data.cmds, new_cmd);

        while (head_parser)
        {
            if (head_parser->type == PIPE)
            {
                new_cmd = init_cmd_node();
                new_cmd->cmd_index = i;
                i++;
                push_back_cmd(&g_data.cmds, new_cmd);
            }
            else if (head_parser->type == EXEC)
            {
                new_cmd->cmd = ft_strdup(head_parser->value->exec_cmd->argv[0]);
                new_cmd->args = ft_strdup_args(head_parser->value->exec_cmd->argv);
            }
            else if (head_parser->type == REDR)
            {
                if (head_parser->value->redr_cmd->type_redr == '<')
                    handle_in_file(new_cmd, *(head_parser->value->redr_cmd->list_file_name));
                else if (head_parser->value->redr_cmd->type_redr == '>')
                    handle_out_file(new_cmd, *(head_parser->value->redr_cmd->list_file_name));
                else if (head_parser->value->redr_cmd->type_redr == '+')
                    handle_out_file_append(new_cmd, *(head_parser->value->redr_cmd->list_file_name));
                else if (head_parser->value->redr_cmd->type_redr == '-')
                    handle_herdoc(new_cmd, *(head_parser->value->redr_cmd->list_file_name));
            }
            head_parser = head_parser->next;
        }
        g_data.n_of_cmd = i;
    }
}