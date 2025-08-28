/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:29:13 by osancak           #+#    #+#             */
/*   Updated: 2025/08/28 12:52:45 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*strip_quote(char *token)
{
	if (token && token[0] == ARG_PIPE_SEPARATOR)
		return (token + 1);
	return (token);
}

static char	*group_seperator(char *str)
{
	char	*new;

	if (!str)
		return (NULL);
	new = malloc(ft_strlen(str) + 2);
	if (!new)
		return (NULL);
	new[0] = ARG_PIPE_SEPARATOR;
	ft_memcpy(new + 1, str, ft_strlen(str) + 1);
	free(str);
	return (new);
}

void	add_quoted_token(char **merged, char *tmp)
{
	if (!*merged)
	{
		*merged = malloc(ft_strlen(tmp) + 2);
		if (*merged)
		{
			(*merged)[0] = ARG_PIPE_SEPARATOR;
			ft_memcpy(*merged + 1, tmp, ft_strlen(tmp) + 1);
		}
	}
	else
	{
		if ((*merged)[0] != ARG_PIPE_SEPARATOR)
			*merged = group_seperator(*merged);
		*merged = ft_strjoin(*merged, tmp, 1);
	}
}

void	handle_quoted_part(const char *input, int *i, char **merged)
{
	char	*tmp;
	char	quote;
	int		start;
	t_vars	*vars;

	vars = static_vars(NULL);
	quote = input[(*i)++];
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
	{
		vars->last_exit_code = 333;
		return ;
	}
	tmp = make_token(input, start, *i);
	add_quoted_token(merged, tmp);
	free(tmp);
	if (input[*i])
		(*i)++;
}

void	handle_unquoted_part(const char *input, int *i, char **merged)
{
	int		start;
	char	*tmp;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '\''
		&& input[*i] != '"' && !ft_ismeta(input[*i]))
		(*i)++;
	tmp = make_token(input, start, *i);
	if (!*merged)
		*merged = tmp;
	else
		*merged = ft_strjoin(*merged, tmp, 3);
}
