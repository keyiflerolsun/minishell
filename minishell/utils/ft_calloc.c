/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:50:14 by osancak           #+#    #+#             */
/*   Updated: 2025/08/09 13:06:34 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = 0;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (!nmemb || !size)
		return (malloc(0));
	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	ft_bzero(res, nmemb * size);
	return (res);
}
