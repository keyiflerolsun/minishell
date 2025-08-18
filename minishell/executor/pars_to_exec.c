/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:28:55 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 13:17:47 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

static void	wait_child_exec(t_vars *vars, char **cmd)
{
	waitpid(child_exec(vars, cmd), &vars->last_exit_code, 0);
	if (WIFEXITED(vars->last_exit_code))
		vars->last_exit_code = WEXITSTATUS(vars->last_exit_code);
	else
		vars->last_exit_code = EXIT_FAILURE;
}

void	pars_to_exec(t_vars *vars)
{
	// if (builtin_exec(vars, vars->tokens))
	// 	return ;
	// wait_child_exec(vars, vars->tokens);
	t_list	*cmds;
	t_pipe	pipe;
	t_cmd	*cmd;

	cmds = vars->cmds;
	pipe.cmd_count = ft_lstsize(cmds);
	pipe.cmd_index = 0;
	while (cmds)
	{
		cmd = (t_cmd *)cmds->data;
		if (!builtin_exec(vars, cmd->args))
			wait_child_exec(vars, cmd->args);
		cmds = cmds->next;
		pipe.cmd_index++;
	}
}
