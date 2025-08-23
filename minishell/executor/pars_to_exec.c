/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:28:55 by osancak           #+#    #+#             */
/*   Updated: 2025/08/23 17:08:11 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

static void	wait_child_exec(t_vars *vars, t_pipes *pipes, char **cmd)
{
	waitpid(child_exec(vars, pipes, cmd), &vars->last_exit_code, 0);
	if (WIFEXITED(vars->last_exit_code))
		vars->last_exit_code = WEXITSTATUS(vars->last_exit_code);
	else
		vars->last_exit_code = EXIT_FAILURE;
}

static void	init_pipes(t_vars *vars, t_pipes *pipes)
{
	pipes->cmd_list = vars->cmds;
	pipes->cmd_count = ft_lstsize(pipes->cmd_list);
	pipes->cmd_index = 0;
	pipes->infile = STDIN_FILENO;
	pipes->outfile = STDOUT_FILENO;
	pipes->last_read = pipes->infile;
}

static void	continue_pipes(t_vars *vars, t_pipes *pipes)
{
	clean_pipe(pipes);
	pipes->exit_codes[pipes->cmd_index] = vars->last_exit_code;
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
		if (cmd->infile)
			init_infile(pipes);
		if (cmd->outfile)
			init_outfile(pipes);
		if (!builtin_exec(vars, pipes, cmd->args))
			wait_child_exec(vars, pipes, cmd->args);
		continue_pipes(vars, pipes);
	}
	return (res);
}

void	pars_to_exec(t_vars *vars)
{
	t_pipes	pipes;
	t_cmd	*cmd;

	init_pipes(vars, &pipes);
	while (pipes.cmd_list)
	{
		cmd = (t_cmd *)pipes.cmd_list->data;
		setup_pipe(&pipes);
		if (ft_is_operator(vars, &pipes, cmd))
			continue ;
		if (!builtin_exec(vars, &pipes, cmd->args))
			wait_child_exec(vars, &pipes, cmd->args);
		continue_pipes(vars, &pipes);
	}
	close_fd(pipes);
}
