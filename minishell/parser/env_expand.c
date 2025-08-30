/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:54:47 by osancak           #+#    #+#             */
/*   Updated: 2025/08/30 12:11:30 by osancak          ###   ########.fr       */
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

static void	expand_init(t_expander *expender)
{
	expender->res = NULL;
	expender->q[0] = 0;
	expender->q[1] = 0;
	expender->i = 0;
}

static void	join_sstuuf(char **res, char *tmp, size_t *i, char const *line)
{
	tmp[0] = line[(*i)++];
	tmp[1] = '\0';
	*res = ft_strjoin(*res, tmp, 1);
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
	if (!val)
		return (NULL);
	return (val);
}

char	*expand_env(t_vars vars, const char *line)
{
	t_expander	expander;
	char		*val;

	expand_init(&expander);
	while (line[expander.i])
	{
		if (line[expander.i] == '\'' && !expander.q[1])
			expander.q[0] = !expander.q[0];
		else if (line[expander.i] == '"' && !expander.q[0])
			expander.q[1] = !expander.q[1];
		else if (line[expander.i] == '$' && is_special_dollar(line[expander.i + 1]) && !expander.q[0])
		{
			join_sstuuf(&expander.res, expander.tmp, &expander.i, line);
			continue ;
		}
		else if (line[expander.i] == '$' && !expander.q[0] && !is_heredot(line, expander.i))
		{
			val = handle_dollar(line, &expander.i, vars);
			expander.res = ft_strjoin(expander.res, val, 3);
			continue ;
		}
		join_sstuuf(&expander.res, expander.tmp, &expander.i, line);
	}
	return (expander.res);
}
