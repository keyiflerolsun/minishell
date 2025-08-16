/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:54:47 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 14:56:08 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

char	*expand_var(const char *line, size_t *i, char **envp)
{
	size_t	st;
	char	*val;
	char	*key;

	st = *i;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	key = ft_substr(line, st, *i - st);
	val = get_env_value(envp, key);
	free(key);
	return (val);
}

char	*expand_env(const char *line, char **envp)
{
	char	*res;
	int		q[2]; // q[0] = tek_tırnak, q[1] = çift tırjnak
	char	tmp[2];
	char	*val;
	size_t	i;

	res = ft_strdup("");
	q[0] = 0;
	q[1] = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !q[1])
			q[0] = !q[0];
		else if (line[i] == '"' && !q[0])
			q[1] = !q[1];
		else if (line[i] == '$' && !q[0])
		{
			i++;
			val = expand_var(line, &i, envp);
			res = ft_strjointwo(res, val);
			free(val);
			continue ;
		}
		tmp[0] = line[i++];
		tmp[1] = '\0';
		res = ft_strjointwo(res, tmp);
	}
	return (res);
}
