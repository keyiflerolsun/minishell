/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:28:55 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 14:37:07 by osancak          ###   ########.fr       */
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
	t_pipes	pipes;
	t_cmd	*cmd;

	pipes.cmd_list = vars->cmds;
	pipes.cmd_count = ft_lstsize(pipes.cmd_list);
	pipes.cmd_index = 0;
	while (pipes.cmd_list)
	{
		cmd = (t_cmd *)pipes.cmd_list->data;
		if (!cmd->infile
			&& !cmd->outfile
			&& !cmd->here_doc
			&& !builtin_exec(vars, cmd->args))
			wait_child_exec(vars, cmd->args);
		pipes.exit_codes[pipes.cmd_index] = vars->last_exit_code;
		pipes.cmd_list = pipes.cmd_list->next;
		pipes.cmd_index++;
	}
}
