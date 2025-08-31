/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_aware_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:15:43 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/31 19:34:55 by osancak          ###   ########.fr       */
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

char	*make_token(const char *input, int start, int end)
{
	char	*token;

	token = malloc(end - start + 1);
	if (!token)
		return (NULL);
	ft_memcpy(token, input + start, end - start);
	token[end - start] = '\0';
	return (token);
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
		if (ft_ismeta(input[i]))
			handle_metachar(&arr, input, &i);
		else
			handle_token(&arr, input, &i);
	}
	add_token(&arr, NULL);
	return (arr.tokens);
}

int	is_heredot(const char *line, size_t d_i)
{
	int	i;
	int	end;
	int	start;
	int	len;

	i = d_i - 1;
	while (i >= 0 && ft_isspace(line[i]))
		i--;
	end = i;
	while (i >= 0 && !ft_isspace(line[i]))
		i--;
	start = i + 1;
	len = end - start + 1;
	if (len == 2 && line[start] == '<' && line[start + 1] == '<')
		return (1);
	return (0);
}
