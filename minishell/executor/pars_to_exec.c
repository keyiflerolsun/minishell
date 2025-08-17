/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:28:55 by osancak           #+#    #+#             */
/*   Updated: 2025/08/17 15:37:49 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"

static int	is_builtin(t_vars *vars, char **tokens)
{
	if (!ft_strcmp(*tokens, "pwd"))
		return (ft_pwd(tokens, vars), 1);
	else if (!ft_strcmp(*tokens, "env"))
		return (ft_env(tokens, vars), 1);
	else if (!ft_strcmp(*tokens, "echo"))
		return (ft_echo(tokens, vars), 1);
	else if (!ft_strcmp(*tokens, "export"))
		return (ft_export(tokens, vars), 1);
	else if (!ft_strcmp(*tokens, "unset"))
		return (ft_unset(tokens, vars), 1);
	else if (!ft_strcmp(*tokens, "cd"))
		return (ft_cd(tokens, vars), 1);
	else if (!ft_strcmp(*tokens, "exit"))
		return (ft_exit(tokens, vars), 1);
	return (0);
}

void	pars_to_exec(t_vars *vars)
{
	if (!is_builtin(vars, vars->tokens))
	{
		waitpid(ft_execute(*vars, vars->tokens), &vars->last_exit_code, 0);
		if (WIFEXITED(vars->last_exit_code))
			vars->last_exit_code = WEXITSTATUS(vars->last_exit_code);
		else
			vars->last_exit_code = EXIT_FAILURE;
	}
}
