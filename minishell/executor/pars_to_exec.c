/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:28:55 by osancak           #+#    #+#             */
/*   Updated: 2025/08/31 17:03:47 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

static void	ft_exec(t_vars *vars, t_pipes *pipes, t_cmd *cmd)
{
	if (cmd->args && cmd->args[0])
		if (!builtin_exec(vars, pipes, cmd->args))
			pipes->cmds[pipes->cmd_index] = child_exec(vars, pipes, cmd->args);
}

static int	ft_is_operator(t_vars *vars, t_pipes *pipes, t_cmd *cmd)
{
	int	res;

	res = 0;
	if (cmd->infile || cmd->outfile || cmd->here_doc)
	{
		res = 1;
		if (cmd->here_doc)
			ft_heredot(vars, pipes, cmd->limiter);
		if (cmd->infile)
			init_infile(pipes);
		if (cmd->outfile)
			init_outfile(pipes);
		if (vars->last_exit_code == 130 || vars->last_exit_code == EXIT_FAILURE)
			return (res);
		ft_exec(vars, pipes, cmd);
	}
	return (res);
}

void	pars_to_exec(t_vars *vars)
{
	t_pipes	pipes;
	t_cmd	*cmd;

	if (!init_pipes(vars, &pipes))
		return ;
	while (pipes.cmd_list)
	{
		update_vars(vars);
		cmd = (t_cmd *)pipes.cmd_list->data;
		setup_pipe(&pipes);
		if (ft_is_operator(vars, &pipes, cmd))
		{
			continue_pipes(vars, &pipes);
			continue ;
		}
		ft_exec(vars, &pipes, cmd);
		continue_pipes(vars, &pipes);
	}
	pipes.cmd_index = -1;
	while (pipes.cmd_index++ < pipes.cmd_count - 1)
		ft_wait_pid(vars, pipes.cmds[pipes.cmd_index]);
	close_fd(pipes);
	unlink("here_doc");
}
