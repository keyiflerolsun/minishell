/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:51:35 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/25 13:32:42 by osancak          ###   ########.fr       */
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
