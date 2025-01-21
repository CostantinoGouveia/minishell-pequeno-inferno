
#include "minishell.h"


static int	have_quotes(char *s1);
static char	*handle_trim_quotes(char const *s1, int *val);

static int	have_quotes(char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == '\"' || s1[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

static char	*handle_trim_quotes(char const *s1, int *val)
{
	char	*s2;
	char	sig;
	int		i;

	sig = '\1';
	i = 0;
	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	while (*s1)
	{
		if (sig == '\1' && (*s1 == '\"' || *s1 == '\''))
		{
			sig = *s1++;
			(*val)++;
		}
		else if (*s1 == sig)
		{
			sig = '\1';
			s1++;
			(*val)++;
		}
		else
			s2[i++] = *s1++;
	}
	s2[i] = '\0';
	return (s2);
}
char	*strtrim_quote(char *str)
{
	int		val;
	char	*tmp;

	val = 0;
	if (!have_quotes(str))
		return (str);
	tmp = handle_trim_quotes(str, &val);
	if (!(val % 2) && tmp)
	{
		free(str);
		return (tmp);
	}
	else
		free(tmp);
	return (str);
}

void	strtrim_quotes(char **arr)
{
	int		i;

	i = 0;
	while (arr && arr[i] != NULL)
	{
		arr[i] = strtrim_quote(arr[i]);
		i++;
	}
}
