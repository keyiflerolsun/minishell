/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:51:35 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/11 16:05:36 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

t_token_array	*init_token(t_token_array *arr)
{
	arr->size = 0;
	arr->capacity = 10;
	arr->tokens = malloc(arr->capacity * sizeof(char *));
	if (!arr->tokens)
		return (NULL);
	return (arr);
}

static char	*remove_quotes(char *token)
{
	int		len;
	char	*res;

	len = ft_strlen(token);
	res = malloc(len - 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, token + 1, len - 2);
	res[len - 2] = '\0';
	return (res);
}

char	*quote_with_space_inside(char *first, char *token)
{
	if (*first == '"' && ft_strchr(token + 1, '\''))
		return (remove_quotes(token));
	if (*first == '\'' && ft_strchr(token + 1, '"'))
		return (remove_quotes(token));
	return (ft_strdup(token));
}

char	*process_token(char *token)
{
	int		len;
	int		has_space;
	int		i;
	char	first;
	char	last;

	len = ft_strlen(token);
	if (len < 2)
		return (ft_strdup(token));
	first = token[0];
	last = token[len - 1];
	if ((first == '\'' && last == '\'') || (first == '"' && last == '"'))
	{
		has_space = 0;
		i = 0;
		while (++i < len - 1)
			if (token[i] == ' ')
				has_space = 1;
		if (has_space)
		{
			return (quote_with_space_inside(&first, token));
		}
		return (remove_quotes(token));
	}
	return (ft_strdup(token));
}
