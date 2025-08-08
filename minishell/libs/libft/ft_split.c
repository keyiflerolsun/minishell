/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 08:17:20 by osancak           #+#    #+#             */
/*   Updated: 2025/06/15 18:24:59 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	res;

	res = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			res++;
		while (*s && *s != c)
			s++;
	}
	return (res + 1);
}

static void	ft_free(char **res, int n)
{
	while (n--)
		free(res[n]);
	free(res);
}

static int	ft_do_split(char const *str, char chr, char **res)
{
	int	count;
	int	len;

	count = 0;
	while (*str)
	{
		while (*str == chr)
			str++;
		if (!*str)
			break ;
		len = 0;
		while (str[len] && str[len] != chr)
			len++;
		res[count] = ft_substr(str, 0, len);
		if (!res[count])
		{
			ft_free(res, count);
			return (-1);
		}
		count++;
		str += len;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = ft_count(s, c);
	res = ft_calloc(word_count, sizeof(char *));
	if (!res)
		return (NULL);
	if (ft_do_split(s, c, res) < 0)
		return (NULL);
	return (res);
}
