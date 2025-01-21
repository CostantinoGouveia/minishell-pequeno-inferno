
#include "minishell.h"

t_command	*find_tail(t_command *head)
{
	t_command	*current;

	if (!head)
		return (NULL);
	current = head;
	while (current->next)
		current = current->next;
	return (current);
}

char	**cpy_arr(char **map)
{
	int		i;
	char	**new;

	i = 0;
	while (map[i])
		i++;
	new = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (map[i])
	{
		new[i] = ft_strdup(map[i]);
		i++;
	}
	return (new);
}

void	new_struct(t_prompt *prompt, t_command **head)
{
	t_command	*new;
	t_command	*current;

	new = ft_calloc(1, sizeof(t_command));
	if (prompt && prompt->args[0])
	{
		new->args = expander_args(cpy_arr(prompt->args));
		strtrim_quotes(new->args);
		new->path = cmd_path(new->args[0]);
	}
	new->prompt = prompt;
	new->fd[0] = -1;
	new->fd[1] = -1;
	new->infile_fd = -1;
	new->outfile_fd = -1;
	new->is_last = 0;
	new->is_exec = (prompt->args[0] && *prompt->args[0] != '\0');
	if (!*head)
	{
		*head = new;
		return ;
	}
	current = find_tail(*head);
	current->next = new;
}

void	print_commands(t_command *head)
{
	t_command	*current;

	current = head;
	while (current)
	{
		if (current->args)
			print_arr(current->args);
		printf("Path: %s\n", current->path);
		printf("Fds: %d, %d\n", current->fd[0], current->fd[1]);
		printf("Infile_fd: %d Outfile_fd: %d\n", \
				current->infile_fd, current->outfile_fd);
		printf("Current: %p\n", current);
		printf("Next: %p\n\n\n", current->next);
		current = current->next;
	}
}

t_command	*init_exec(t_prompt *prompt)
{
	t_command	*head;
	t_command	*tail;

	head = NULL;
	while (prompt)
	{
		new_struct(prompt, &head);
		prompt = prompt->next;
	}
	if (list_len(head) == 1)
		data()->single_cmd = 1;
	else
		data()->single_cmd = 0;
	tail = find_tail(head);
	tail->is_last = 1;
	return (head);
}
