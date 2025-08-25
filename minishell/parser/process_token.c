/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:51:35 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/24 17:21:33 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


t_token_array	*init_token(t_token_array *arr)
{
	arr->size = 0;
	arr->capacity = 10;
	arr->tokens = malloc(arr->capacity * sizeof(char *));
	if (!arr->tokens)
		return (NULL);
	return (arr);
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


static void	add_quoted_token(char **merged, char *tmp)
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

static void	handle_quoted_part(const char *input, int *i, char **merged)
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
		free(*merged);
		return ;
	}
	tmp = make_token(input, start, *i);
	add_quoted_token(merged, tmp);
	free(tmp);
	if (input[*i])
		(*i)++;
}

static void	handle_unquoted_part(const char *input, int *i, char **merged)
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

void	handle_token(t_token_array *arr, const char *input, int *i)
{
	char	*merged;

	merged = NULL;
	while (input[*i] && !ft_isspace(input[*i]) && !ft_ismeta(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
			handle_quoted_part(input, i, &merged);
		else
			handle_unquoted_part(input, i, &merged);
	}
	if (merged)
		add_token(arr, merged);
}

void	handle_metachar(t_token_array *arr, const char *input, int *i)
{
	if ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>'
			&& input[*i + 1] == '>'))
	{
		add_token(arr, make_token(input, *i, *i + 2));
		*i += 2;
	}
	else
	{
		add_token(arr, make_token(input, *i, *i + 1));
		(*i)++;
	}
}
