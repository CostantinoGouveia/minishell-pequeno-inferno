/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:05:10 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/07 11:05:12 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_str(char *str)
{
	int	len;

	len = 0;
	if (str && *str == '$' && *str++)
	{
		if (ft_isdigit(*str))
			return (1);
		while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
			len++;
		if (len == 0 && *str == '?')
			len = 1;
		if (len == 0 && *str != '\"' && *str != '\'')
			return (-1);
		return (len);
	}
	return (-1);
}

static char	*expander(char *str, int start, int len)
{
	char	*key;
	char	*value;
	char	*part1;
	char	*part2;
	char	*result;

	key = ft_substr(str, start + 1, len);
	value = get_value(key);
	part2 = &str[start + 1 + len];
	str[start] = 0;
	part1 = str;
	free(key);
	key = ft_strjoin(part1, value);
	result = ft_strjoin(key, part2);
	free(key);
	free(str);
	if (result && *result == '\0')
	{
		free(result);
		return (NULL);
	}
	return (expander_str(result));
}

char	*expander_str(char *str)
{
	size_t	i;
	char	flag;
	int		len;

	i = 0;
	flag = 0;
	len = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (flag == 0 && (str[i] == '\'' || str[i] == '\"'))
			flag = str[i];
		else if (flag == str[i])
			flag = 0;
		else if (flag != '\'')
		{
			len = check_str(&str[i]);
			if (len != -1)
				return (expander(str, i, len));
		}
		i++;
	}
	return (str);
}

char	**expander_args(char **args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "\"\'$\'\"") || \
			!ft_strcmp(args[i], "\"$\""))
			i++;
		args[i] = expander_str(args[i]);
		if (args[i] == NULL)
		{
			j = i;
			while (args[++j])
			{
				args[j - 1] = args[j];
				args[j] = NULL;
			}
		}
		else
			i++;
	}
	return (args);
}
