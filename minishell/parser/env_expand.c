/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:54:47 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 20:54:13 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*expand_var(const char *line, size_t *i, char **envp)
{
	size_t	st;
	char	*val;
	char	*key;

	st = *i;
	while (ft_isalnum(line[*i]) || line[*i] == '_' || line[*i] == '?')
		(*i)++;
	key = ft_substr(line, st, *i - st);
	val = get_env_value(envp, key);
	free(key);
	return (val);
}

static void	expand_init(int *q, char **res, size_t *i)
{
	*res = ft_strdup("");
	q[0] = 0;
	q[1] = 0;
	*i = 0;
}

static void	join_sstuuf(char **res, char *tmp, size_t *i, char const *line)
{
	tmp[0] = line[(*i)++];
	tmp[1] = '\0';
	*res = parser_join(*res, tmp);
}

static char	*handle_dollar(const char *line, size_t *i, t_vars vars)
{
	char	*val;

	if (line[*i + 1] == '?')
	{
		(*i) += 2;
		return (ft_itoa(vars.last_exit_code));
	}
	(*i)++;
	val = expand_var(line, i, vars.ep);
	return (val);
}

char	*expand_env(t_vars vars, const char *line)
{
	char	*res;
	int		q[2];
	char	tmp[2];
	char	*val;
	size_t	i;

	expand_init(q, &res, &i);
	while (line[i])
	{
		if (line[i] == '\'' && !q[1])
			q[0] = !q[0];
		else if (line[i] == '"' && !q[0])
			q[1] = !q[1];
		else if (line[i] == '$' && !q[0])
		{
			val = handle_dollar(line, &i, vars);
			res = parser_join(res, val);
			free(val);
			continue ;
		}
		join_sstuuf(&res, tmp, &i, line);
	}
	return (res);
}
