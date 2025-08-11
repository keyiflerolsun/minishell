/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_aware_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:15:43 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/11 16:05:40 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_token(t_token_array *arr, char *token)
{
	int		i;
	int		new_cap;
	char	**new_tokens;

	if (arr->size == arr->capacity)
	{
		new_cap = arr->capacity * 2;
		new_tokens = malloc(new_cap * sizeof(char *));
		if (!new_tokens)
			return ;
		i = -1;
		while (++i < arr->size)
			new_tokens[i] = arr->tokens[i];
		free(arr->tokens);
		arr->tokens = new_tokens;
		arr->capacity = new_cap;
	}
	arr->tokens[arr->size++] = token;
}

static char	*make_token(const char *input, int start, int end)
{
	char	*token;
	int		len;

	len = end - start;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_memcpy(token, input + start, len);
	token[len] = '\0';
	return (token);
}

static void	handle_quoted_token(t_token_array *arr, const char *input, int *i)
{
	char	quote_char;
	int		start;
	char	*token;

	quote_char = input[(*i)++];
	start = *i;
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	token = make_token(input, start, *i);
	if (input[*i])
		(*i)++;
	add_token(arr, ft_strjoin_three(quote_char, token, quote_char));
	free(token);
}

static void	handle_unquoted_token(t_token_array *arr, const char *input, int *i)
{
	int		start;
	char	*token;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '\''
		&& input[*i] != '"')
		(*i)++;
	token = make_token(input, start, *i);
	add_token(arr, token);
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
		if (input[i] == '\'' || input[i] == '"')
			handle_quoted_token(&arr, input, &i);
		else
			handle_unquoted_token(&arr, input, &i);
	}
	add_token(&arr, NULL);
	return (arr.tokens);
}
