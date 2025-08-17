/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:44:32 by osancak           #+#    #+#             */
/*   Updated: 2025/08/17 13:57:33 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_cd(char **tokens, t_vars *vars)
{
	char	*old;

	if (!tokens[1])
	{
		write_err(tokens[0], "RTFM! » with only a relative or absolute path\n");
		vars->last_exit_code = 42;
		return ;
	}
	if (chdir(tokens[1]) != 0)
	{
		write_perr(tokens[1]);
		vars->last_exit_code = errno;
		return ;
	}
	old = get_env(vars->env, "PWD");
	update_env(&vars->env, "OLDPWD", old);
	free(old);
	update_env(&vars->env, "PWD", tokens[1]);
	vars->last_exit_code = EXIT_SUCCESS;
}
