/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:28:55 by osancak           #+#    #+#             */
/*   Updated: 2025/08/29 16:32:16 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "parser.h"

static int	init_pipes(t_vars *vars, t_pipes *pipes)
{
	if (vars->last_exit_code == 333)
	{
		vars->last_exit_code = 2;
		return (write_err("minismet", "syntax error\n"), 0);
	}
	pipes->cmd_list = vars->cmds;
	pipes->cmd_count = ft_lstsize(pipes->cmd_list);
	pipes->cmd_index = 0;
	pipes->infile = STDIN_FILENO;
	pipes->outfile = STDOUT_FILENO;
	pipes->last_read = pipes->infile;
	return (1);
}

static void	continue_pipes(t_vars *vars, t_pipes *pipes)
{
	pipes->exit_codes[pipes->cmd_index] = vars->last_exit_code;
	clean_pipe(pipes);
	pipes->cmd_list = pipes->cmd_list->next;
	pipes->cmd_index++;
}

static int	ft_is_operator(t_vars *vars, t_pipes *pipes, t_cmd *cmd)
{
	int	res;

	res = 0;
	if (cmd->infile || cmd->outfile || cmd->here_doc)
	{
		res = 1;
		if (cmd->here_doc)
			ft_heredot(vars, cmd->limiter);
		if (cmd->infile)
			init_infile(pipes);
		if (cmd->outfile)
			init_outfile(pipes);
		if (vars->last_exit_code == 130 || vars->last_exit_code == EXIT_FAILURE)
			return (res);
		if (cmd->args && !builtin_exec(vars, pipes, cmd->args))
			child_exec(vars, pipes, cmd->args);
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
		cmd = (t_cmd *)pipes.cmd_list->data;
		setup_pipe(&pipes);
		if (ft_is_operator(vars, &pipes, cmd))
		{
			continue_pipes(vars, &pipes);
			continue ;
		}
		if (cmd->args && !builtin_exec(vars, &pipes, cmd->args))
			child_exec(vars, &pipes, cmd->args);
		continue_pipes(vars, &pipes);
	}
	close_fd(pipes);
	unlink("here_doc");
}
