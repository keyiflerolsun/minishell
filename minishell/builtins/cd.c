/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:44:32 by osancak           #+#    #+#             */
/*   Updated: 2025/09/01 16:17:54 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_cd_check(t_vars *vars, char **tokens)
{
	if (!tokens[1])
	{
		write_err(tokens[0], "RTFM! » with only a relative or absolute path\n");
		vars->last_exit_code = 42;
		return (0);
	}
	else if (tokens[2])
	{
		write_err("cd", "too many arguments\n");
		vars->last_exit_code = EXIT_FAILURE;
		return (0);
	}
	else if (chdir(tokens[1]) != 0)
	{
		write_perr(tokens[1]);
		vars->last_exit_code = EXIT_FAILURE;
		return (0);
	}
	return (1);
}

void	ft_cd(char **tokens, t_vars *vars)
{
	char	*old;
	char	buff[1024];

	if (!ft_cd_check(vars, tokens))
		return ;
	if (!getcwd(buff, sizeof(buff)))
	{
		vars->last_exit_code = EXIT_FAILURE;
		return ;
	}
	old = get_env(vars->env, "PWD");
	update_env(&vars->env, "OLDPWD", old);
	free(old);
	update_env(&vars->env, "PWD", buff);
	vars->last_exit_code = EXIT_SUCCESS;
}
