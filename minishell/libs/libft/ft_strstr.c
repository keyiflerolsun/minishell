/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:45:56 by osancak           #+#    #+#             */
/*   Updated: 2025/07/07 11:18:40 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	b;
	size_t	l;
	size_t	len;

	if (!*little)
		return ((char *)big);
	b = -1;
	len = ft_strlen(big);
	while (big[++b] && b < len)
	{
		l = 0;
		while (big[b + l] == little[l] && b + l < len)
			if (!little[l++ + 1])
				return ((char *)&big[b]);
	}
	return (NULL);
}
