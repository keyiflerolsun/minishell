/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:27:11 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 15:42:35 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	update_env(t_vars *vars, char *key, char *value)
{
	t_list	*env;
	char	*tmp;

	env = vars->env;
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return ;
	while (env)
	{
		if (!ft_strncmp(env->data, tmp, ft_strlen(tmp)))
		{
			free(env->data);
			env->data = ft_strjoin(tmp, value);
			free(tmp);
			return ;
		}
		env = env->next;
	}
	ft_lstadd_back(&vars->env, ft_lstnew(ft_strjoin(tmp, value)));
	free(tmp);
}

int	is_valid_key(char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = -1;
	while (key[++i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
	}
	return (1);
}

void	ft_export(char **tokens, t_vars *vars)
{
	char	**parts;
	int		count;

	if (tokens[2] || !ft_strchr(tokens[1], '='))
	{
		write_err("export", "options or arguments are not supported\n");
		vars->last_exit_code = EXIT_FAILURE;
		return ;
	}
	parts = ft_split(tokens[1], '=');
	count = 0;
	while (parts[count])
		count++;
	if (count != 2 || !is_valid_key(parts[0]))
	{
		free_split(parts);
		write_err("export", "invalid identifier\n");
		vars->last_exit_code = EXIT_FAILURE;
		return ;
	}
	update_env(vars, parts[0], parts[1]);
	free_split(parts);
	vars->last_exit_code = EXIT_SUCCESS;
}
