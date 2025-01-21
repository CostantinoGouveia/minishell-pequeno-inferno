#include "minishell.h"

char	*ft_strjoin_space(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*aux;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	aux = (char *)malloc(len1 + len2 + 2);
	if (!aux)
		return (NULL);
	while (i < len1)
	{
		aux[i] = s1[i];
		i++;
	}
    aux[len1] = ' ';
	i = 1;
	while (i < len2)
	{
		aux[len1 + i] = s2[i];
		i++;
	}
	aux[len1 + len2] = '\0';
	return (aux);
}

static t_command *create_command_node(t_token **tokens)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd) return NULL;

    cmd->args = strdup((*tokens)->value);  // Primeiro argumento (simples por agora)
    cmd->io_list = NULL;
    cmd->next = NULL;

    *tokens = (*tokens)->next;  // Avança para o próximo token

    while (*tokens && (*tokens)->type != T_PIPE) {
        if ((*tokens)->type == T_LESS || (*tokens)->type == T_GREAT ||
            (*tokens)->type == T_DLESS || (*tokens)->type == T_DGREAT) {
            t_io_list *io = parse_redirections(tokens);
            io->next = cmd->io_list;
            if (cmd->io_list) cmd->io_list->prev = io;
            cmd->io_list = io;
        } else {
            cmd->args = ft_strjoin_space(cmd->args, (*tokens)->value);
            *tokens = (*tokens)->next;  // Ignora outros argumentos por simplicidade
        }
    }
    return cmd;
}

t_command *parse_pipeline(t_token **tokens)
{
    t_command *head = NULL;
    t_command *tail = NULL;

    while (*tokens) {
        t_command *cmd = create_command_node(tokens);
        if (!cmd) {
            free_command_list(head);
            return NULL;
        }
        if (!head) {
            head = cmd;
        } else {
            tail->next = cmd;
        }
        tail = cmd;

        if (*tokens && (*tokens)->type == T_PIPE) {
            *tokens = (*tokens)->next;  // Avança além do pipe
        }
    }
    return head;
}

// Função para liberar a memória da lista de comandos
void free_command_list(t_command *cmd)
{
    while (cmd) {
        t_command *next = cmd->next;
        free_io_list(cmd->io_list);
        free(cmd->args);
        free(cmd);
        cmd = next;
    }
}

t_io_list *parse_redirections(t_token **tokens)
{
    t_io_list *io = malloc(sizeof(t_io_list));
    if (!io)
        return NULL;

    io->type = ((*tokens)->type == T_LESS) ? IO_IN :
               ((*tokens)->type == T_GREAT) ? IO_OUT :
               ((*tokens)->type == T_DLESS) ? IO_HEREDOC : IO_APPEND;

    *tokens = (*tokens)->next;  // Avança para o próximo token
    io->value = strdup((*tokens)->value);
    io->expanded_value = NULL;  // Pode ser expandido depois
    io->prev = io->next = NULL;

    *tokens = (*tokens)->next;
    return io;
}

void free_io_list(t_io_list *io)
{
    t_io_list *tmp;
    while (io) {
        tmp = io;
        io = io->next;
        free(tmp->value);
        free(tmp->expanded_value);  // Se houver
        free(tmp);
    }
}


void print_io_list(t_io_list *io_list)
{
    printf("I/O Redirections:\n");
    while (io_list)
    {
        printf("  Type: %d, Value: %s\n", io_list->type, io_list->value);
        if (io_list->expanded_value)
        {
            printf("  Expanded Values: ");
            for (char **val = io_list->expanded_value; *val; val++)
                printf("%s ", *val);
            printf("\n");
        }
        io_list = io_list->next;
    }
}

void print_command_list(t_command *command)
{
    int index = 0;
    while (command)
    {
        printf("Command %d:\n", index++);
        printf("  Args: %s\n", command->args ? command->args : "NULL");

        if (command->expanded_args)
        {
            printf("  Expanded Args: ");
            for (char **arg = command->expanded_args; *arg; arg++)
                printf("%s ", *arg);
            printf("\n");
        }

        if (command->io_list)
        {
            printf("  IO List:\n");
            t_io_list *io = command->io_list;
            while (io)
            {
                const char *io_type = io->type == IO_IN ? "Input" :
                                      io->type == IO_OUT ? "Output" :
                                      io->type == IO_HEREDOC ? "Heredoc" : "Append";
                printf("    %s: %s\n", io_type, io->value ? io->value : "NULL");
                io = io->next;
            }
        }
        command = command->next;
        if (command)
            printf("\n");
    }
}
