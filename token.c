#include "minishell.h"

int	white_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	just_spaces(char *str)
{
	int	i;
	int	spaces;

	i = 0;
	spaces = 0;
	while (str[i])
	{
		if (white_space(str[i]))
			spaces++;
		i++;
	}
	return (ft_strlen(str) - spaces);
}

char	*str_spaces_end(char *str)
{
	int		end;
	char	*cpy;

	cpy = ft_strdup(str);
	end = ft_strlen(str) - 1;
	while (end > 0 && white_space(cpy[end]))
	{
		cpy[end] = '\0';
		end--;
	}
	return (cpy);
}

char	**ft_lexer(char *s1)
{
	char	*s2;
	char	*s3;
	char	**arr;

	arr = NULL;
	s2 = str_spaces_end(s1);
	s3 = split_pipes(s2);
	free(s2);
	s2 = split_redirects(s3);
	free(s3);
	replace_spaces(s2);
	arr = ft_split(s2, '\2');
	space_end(arr);
	free(s2);
	return (arr);
}

char	*split_redirects(char *s1)
{
	char	*s2;

	s2 = ft_calloc((ft_strlen(s1) * 2 + 1), sizeof(char));
	handle_redirects(s1, s2);
	replace_spaces(s2);
	return (s2);
}

char	*split_pipes(char *s1)
{
	char	*s2;

	s2 = ft_calloc((ft_strlen(s1) * 2 + 1), sizeof(char));
	handle_pipe(s1, s2);
	replace_spaces(s2);
	return (s2);
}

void	space_end(char **tokens)
{
	int	i;
	int	len;

	i = 0;
	while (tokens[i])
		i++;
	i--;
	len = ft_strlen(tokens[i]) - 1;
	if (tokens[i] && !ft_strcmp(tokens[i], " "))
	{
		free(tokens[i]);
		tokens[i] = NULL;
	}
	else if (tokens[i] && tokens[i][len] == ' ')
		tokens[i][len] = '\0';
}

void	handle_pipe(char *s1, char *s2)
{
	char	sig;

	sig = 1;
	while (s1 && *s1)
	{
		if (sig == 1)
		{
			if (*s1 != '\0' && *s1 == '|')
			{
				*s2++ = ' ';
				while (*s1 != '\0' && *s1 == '|')
					*s2++ = *s1++;
				if (*s1 != '\0')
					*s2++ = ' ';
			}
			if (s1 && (*s1 == '\"' || *s1 == '\''))
				sig = *s1;
			if (s1 && s2 && *s1)
				*s2++ = *s1++;
		}
		else
			end_quote(&sig, &s1, &s2);
	}
	if (s2)
		*s2 = '\0';
}

void	handle_redirects(char *s1, char *s2)
{
	char	sig;

	sig = 1;
	while (s1 && *s1)
	{
		if (sig == 1)
		{
			if (*s1 != '\0' && (*s1 == '<' || *s1 == '>'))
			{
				*s2++ = ' ';
				while (*s1 != '\0' && (*s1 == '<' || *s1 == '>'))
					*s2++ = *s1++;
				if (*s1 != '\0')
					*s2++ = ' ';
			}
			if (s1 && (*s1 == '\"' || *s1 == '\''))
				sig = *s1;
			if (s1 && s2 && *s1)
				*s2++ = *s1++;
		}
		else
			end_quote(&sig, &s1, &s2);
	}
	if (s2)
		*s2 = '\0';
}

/**
 * Substitui separador
 * echo "hello      there" how are 'you 'doing? $USER |wc -l >outfile
 * echo/2"hello      there"/2how/2are/2'you 'doing?/2$USER/2|wc/2-l/2>outfile
*/
void	replace_spaces(char *s1)
{
	char	sig;
	int		i;

	sig = 1;
	i = 0;
	while (s1 && s1[i])
	{
		if (sig == 1)
		{
			while (s1 && white_space(s1[i]) && s1[i + 1] != '\0')
				s1[i++] = '\2';
			if (s1 && s1[i] && (s1[i] == '\"' || s1[i] == '\''))
				sig = s1[i];
		}
		else
		{
			if (sig == '\"' || sig == '\'')
			{
				if (s1 && s1[i] == sig)
					sig = 1;
			}
		}
		i++;
	}
	s1[i] = '\0';
}

void	end_quote(char *sig, char **s1, char **s2)
{
	if (*sig == '\"' || *sig == '\'')
	{
		if (**s1 == *sig)
			*sig = 1;
		*(*s2)++ = *(*s1)++;
	}
}

char	**lexer_sintax_error(char *s1)
{
	char	*s2;
	char	*s3;
	char	**arr;

	arr = NULL;
	s2 = str_spaces_end(s1);
	s3 = split_pipes(s2);
	free(s2);
	s2 = split_redirects(s3);
	free(s3);
	replace_spaces(s2);
	arr = ft_split(s2, '\2');
	space_end(arr);
	free(s2);
	return (arr);
}
