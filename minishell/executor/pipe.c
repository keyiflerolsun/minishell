/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 07:38:23 by osancak           #+#    #+#             */
/*   Updated: 2025/08/28 15:49:31 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	setup_pipe(t_pipes *pipes)
{
	if (pipes->cmd_index < pipes->cmd_count - 1)
	{
		if (pipe(pipes->curr_pipe) == -1)
			error_exit("setup_pipe » pipe", NULL);
	}
	else
	{
		pipes->curr_pipe[0] = -1;
		pipes->curr_pipe[1] = -1;
	}
}

int	get_pipe_in(t_pipes *pipes)
{
	if (pipes->infile != STDIN_FILENO)
		return (pipes->infile);
	return (pipes->last_read);
}

int	get_pipe_out(t_pipes *pipes)
{
	if (pipes->outfile != STDOUT_FILENO)
		return (pipes->outfile);
	if (pipes->cmd_index == pipes->cmd_count - 1)
		return (STDOUT_FILENO);
	return (pipes->curr_pipe[1]);
}

void	clean_pipe(t_pipes *pipes)
{
	if (pipes->last_read > 2)
		close(pipes->last_read);
	if (pipes->curr_pipe[1] > 2)
		close(pipes->curr_pipe[1]);
	if (pipes->infile > 2)
	{
		close(pipes->infile);
		pipes->infile = STDIN_FILENO;
	}
	if (pipes->outfile > 2)
	{
		close(pipes->outfile);
		pipes->outfile = STDOUT_FILENO;
	}
	pipes->last_read = pipes->curr_pipe[0];
}
