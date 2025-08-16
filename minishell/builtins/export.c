/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:27:11 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 20:06:51 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_valid_key(char *key)
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

static int	ft_stop(char **tokens, t_vars *vars)
{
	if (!tokens[1])
	{
		vars->last_exit_code = EXIT_SUCCESS;
		return (1);
	}
	if (*tokens[1] == '-')
	{
		write_err(tokens[0], "options are not supported\n");
		vars->last_exit_code = 42;
		return (1);
	}
	if (!ft_strchr(tokens[1], '='))
	{
		vars->last_exit_code = EXIT_SUCCESS;
		return (1);
	}
	return (0);
}

void	ft_export(char **tokens, t_vars *vars)
{
	char	**parts;
	int		count;

	if (ft_stop(tokens, vars))
		return ;
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
