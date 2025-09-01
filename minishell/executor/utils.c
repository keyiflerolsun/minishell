/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:38:58 by osancak           #+#    #+#             */
/*   Updated: 2025/09/01 15:36:30 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"

void	fd_apply(t_pipes *pipes)
{
	int	pipe_in;
	int	pipe_out;

	pipe_in = get_pipe_in(pipes);
	pipe_out = get_pipe_out(pipes);
	if (pipe_in != STDIN_FILENO)
		dup2(pipe_in, STDIN_FILENO);
	if (pipe_out != STDOUT_FILENO)
		dup2(pipe_out, STDOUT_FILENO);
}

void	close_fd(t_pipes *pipes)
{
	close_if_open(&pipes->curr_pipe[0]);
	close_if_open(&pipes->curr_pipe[1]);
	close_if_open(&pipes->last_read);
	close_if_open(&pipes->infile);
	close_if_open(&pipes->outfile);
}

void	ft_wait_pid(t_vars *vars, pid_t pid)
{
	if (!pid)
		return ;
	waitpid(pid, &vars->last_exit_code, 0);
	if (WIFEXITED(vars->last_exit_code))
		vars->last_exit_code = WEXITSTATUS(vars->last_exit_code);
	if (WIFSIGNALED(vars->last_exit_code))
	{
		vars->last_exit_code = WTERMSIG(vars->last_exit_code);
		if (vars->last_exit_code == 2 || vars->last_exit_code == 3)
			vars->last_exit_code += 128;
	}
}

int	init_pipes(t_vars *vars, t_pipes *pipes)
{
	if (vars->last_exit_code == 333)
	{
		vars->last_exit_code = 2;
		return (write_err("minismet", "syntax error\n"), 0);
	}
	pipes->cmd_list = vars->cmds;
	pipes->cmd_count = ft_lstsize(pipes->cmd_list);
	pipes->cmd_index = 0;
	pipes->infile = -1;
	pipes->outfile = -1;
	pipes->last_read = STDIN_FILENO;
	pipes->curr_pipe[0] = -1;
	pipes->curr_pipe[1] = -1;
	return (1);
}

void	continue_pipes(t_vars *vars, t_pipes *pipes)
{
	pipes->exit_codes[pipes->cmd_index] = vars->last_exit_code;
	clean_pipe(pipes);
	pipes->cmd_list = pipes->cmd_list->next;
	pipes->cmd_index++;
}
