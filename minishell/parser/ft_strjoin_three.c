/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:39:34 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/13 20:16:08 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strjoin_three(char first, char *middle, char last)
{
	size_t	len;
	char	*res;

	if (!middle)
		return (NULL);
	len = ft_strlen(middle) + 2;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[0] = first;
	ft_memcpy(res + 1, middle, ft_strlen(middle));
	res[len - 1] = last;
	res[len] = '\0';
	return (res);
}
