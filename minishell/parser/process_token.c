/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:51:35 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/13 20:15:37 by osancak          ###   ########.fr       */
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
