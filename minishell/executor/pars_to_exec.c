/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:28:55 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 12:03:23 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	wait_child_exec(t_vars *vars)
{
	waitpid(child_exec(vars, vars->tokens), &vars->last_exit_code, 0);
	if (WIFEXITED(vars->last_exit_code))
		vars->last_exit_code = WEXITSTATUS(vars->last_exit_code);
	else
		vars->last_exit_code = EXIT_FAILURE;
}

void	pars_to_exec(t_vars *vars)
{
	if (builtin_exec(vars, vars->tokens))
		return ;
	wait_child_exec(vars);
}
