/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:42:41 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 20:55:38 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*ft_strjointwo(char *s1, char *s2)
{
	size_t	total_len;
	char	*str;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(total_len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy(str + ft_strlen(s1), s2, ft_strlen(s2));
	str[total_len] = '\0';
	free(s1);
	return (str);
}

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

char	*get_env_value(char **envp, char *key)
{
	size_t	len;
	int		i;

	len = ft_strlen(key);
	i = 0;
	while (envp && envp[i])
	{
		if (!strncmp(envp[i], key, len) && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}
