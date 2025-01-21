#include "minishell.h"

char	*etoa(char *name, char *value)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	new = ft_calloc(ft_strlen(name) + ft_strlen(value) + 2, sizeof(char));
	while (name[i])
	{
		new[i] = name[i];
		i++;
	}
	new[i] = '=';
	j = 0;
	while (value && value[j])
	{
		new[i + j] = value[j];
		j++;
	}
	return (new);
}

char	**update_env(char **old)
{
	t_envp	*current;
	int		i;
	char	**new;

	free_arr(old);
	i = 0;
	current = data()->envp;
	while (current && current->name)
	{
		i++;
		current = current->next;
	}
	new = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	current = data()->envp;
	while (current)
	{
		new[i] = etoa(current->name, current->value);
		i++;
		current = current->next;
	}
	new[i] = NULL;
	return (new);
}

void	update_shlvl(char **envp)
{
	int		i;
	int		shlvl;
	char	*new;

	i = 0;
	while (ft_strncmp(envp[i], "SHLVL", 5))
		i++;
	new = ft_substr(envp[i], 6, ft_strlen(envp[i]));
	shlvl = ft_atoi(new);
	free(new);
	free(envp[i]);
	new = ft_itoa(shlvl + 1);
	envp[i] = ft_strjoin("SHLVL=", new);
	free(new);
}

void	no_envp(void)
{
	char	*pwd;
	char	**tmp;

	pwd = getcwd(NULL, 0);
	tmp = ft_calloc(3, sizeof(char *));
	tmp[0] = ft_strjoin("PWD=", pwd);
	tmp[1] = ft_strdup("SHLVL=1");
	tmp[2] = NULL;
	free(pwd);
	getevarr()->envp = tmp;
}

void	new_envp(char **envp)
{
	t_envp	*getev;
	char	**tmp;

	getev = NULL;
	if (!envp || !envp[0])
	{
		no_envp();
		fill_envp(&getev, getevarr()->envp);
		data()->envp = getev;
	}
	else
	{
		tmp = envp_exec(envp);
		update_shlvl(tmp);
		getevarr()->envp = tmp;
		fill_envp(&getev, getevarr()->envp);
		data()->envp = getev;
	}
}