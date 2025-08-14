/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_aware_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:15:43 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/13 20:14:49 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_token(t_token_array *arr, char *token)
{
	int		new_cap;
	char	**new_tokens;
	int		i;

	if (arr->size == arr->capacity)
	{
		new_cap = arr->capacity * 2;
		new_tokens = malloc(new_cap * sizeof(char *));
		if (!new_tokens)
			return ;
		i = 0;
		while (i < arr->size)
		{
			new_tokens[i] = arr->tokens[i];
			i++;
		}
		free(arr->tokens);
		arr->tokens = new_tokens;
		arr->capacity = new_cap;
	}
	arr->tokens[arr->size++] = token;
}

static int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static char	*make_token(const char *input, int start, int end)
{
	char	*token;

	token = malloc(end - start + 1);
	if (!token)
		return (NULL);
	ft_memcpy(token, input + start, end - start);
	token[end - start] = '\0';
	return (token);
}

static void	handle_quoted_part(const char *input, int *i, char **merged)
{
	char	quote;
	int		start;
	char	*tmp;
	char	*old;

	quote = input[(*i)++];
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	tmp = make_token(input, start, *i);
	if (!*merged)
		*merged = ft_strdup(tmp);
	else
	{
		old = *merged;
		*merged = ft_strjoin(*merged, tmp);
		free(old);
	}
	free(tmp);
	if (input[*i])
		(*i)++;
}

static void	handle_unquoted_part(const char *input, int *i, char **merged)
{
	int		start;
	char	*tmp;
	char	*old;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '\''
		&& input[*i] != '"' && !is_metachar(input[*i]))
		(*i)++;
	tmp = make_token(input, start, *i);
	if (!*merged)
		*merged = tmp;
	else
	{
		old = *merged;
		*merged = ft_strjoin(*merged, tmp);
		free(old);
		free(tmp);
	}
}

static void	handle_token(t_token_array *arr, const char *input, int *i)
{
	char	*merged;

	merged = NULL;
	while (input[*i] && !ft_isspace(input[*i]) && !is_metachar(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
			handle_quoted_part(input, i, &merged);
		else
			handle_unquoted_part(input, i, &merged);
	}
	if (merged)
		add_token(arr, merged);
}

static void	handle_metachar(t_token_array *arr, const char *input, int *i)
{
	if ((input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>'))
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

char	**quote_aware_split(const char *input)
{
	t_token_array	arr;
	int				i;
	int				len;

	init_token(&arr);
	i = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		while (i < len && ft_isspace(input[i]))
			i++;
		if (i >= len)
			break ;
		if (is_metachar(input[i]))
			handle_metachar(&arr, input, &i);
		else
			handle_token(&arr, input, &i);
	}
	add_token(&arr, NULL);
	return (arr.tokens);
}