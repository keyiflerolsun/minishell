/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:51:35 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/14 18:47:41 by osancak          ###   ########.fr       */
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

void	handle_quoted_part(const char *input, int *i, char **merged)
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

void	handle_unquoted_part(const char *input, int *i, char **merged)
{
	int		start;
	char	*tmp;
	char	*old;

	start = *i;
	while (
		input[*i]
		&& !ft_isspace(input[*i])
		&& input[*i] != '\'' && input[*i] != '"'
		&& !is_metachar(input[*i])
	)
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

void	handle_token(t_token_array *arr, const char *input, int *i)
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

void	handle_metachar(t_token_array *arr, const char *input, int *i)
{
	if (
		(input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>')
	)
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
