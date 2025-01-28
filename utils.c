#include "minishell.h"

t_redirect	*insert_end_redirects(t_redirect **root)
{
	t_redirect	*new_node;
	t_redirect	*curr;

	new_node = ft_calloc(1, sizeof(t_redirect));
	if (!new_node)
		exit(1);
	if (!*root)
	{
		*root = new_node;
		return (new_node);
	}
	curr = *root;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
	return (new_node);
}

t_args	*insert_end_args(t_args **root)
{
	t_args	*new_node;
	t_args	*curr;

	new_node = ft_calloc(1, sizeof(t_args));
	if (!new_node)
		exit(1);
	if (!*root)
	{
		*root = new_node;
		return (new_node);
	}
	curr = *root;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
	return (new_node);
}

int	count_tokens(char **tokens)
{
	int	len;

	len = 0;
	while (tokens[len])
		len++;
	return (len);
}


void	update_value(char *name, char *value)
{
	t_envp		*current;

	current = data()->envp;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			if (current->value && value)
				current->value = ft_strdup(value);
			else
				current->value = NULL;
			return ;
		}
		current = current->next;
	}
	current = insert_end_envp(&data()->envp);
	current->name = ft_strdup(name);
	current->value = ft_strdup(value);
}

char	*get_value(char *name)
{
	static char	str[20];
	char		*status;
	t_envp		*current;
	size_t		i;

	current = data()->envp;
	if (ft_strcmp("?", name) == 0)
	{
		status = ft_itoa(data()->exit_status);
		i = -1;
		while (status[++i])
			str[i] = status[i];
		str[i] = '\0';
		free(status);
		return (str);
	}
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return ("\0");
}

int	node_exists(char *name)
{
	t_envp	*current;

	current = data()->envp;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

t_envp	*get_node(char *name)
{
	t_envp	*current;

	current = data()->envp;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_data	*data(void)
{
	static t_data	d;

	return (&d);
}


t_envparr	*getevarr(void)
{
	static t_envparr	envp;

	return (&envp);
}

int	list_len(t_command *head)
{
	t_command	*current;
	int			i;

	current = head;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}