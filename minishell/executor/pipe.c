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

void	close_if_open(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

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
	if (pipes->infile != -1)
		return (pipes->infile);
	return (pipes->last_read);
}

int	get_pipe_out(t_pipes *pipes)
{
	if (pipes->outfile != -1)
		return (pipes->outfile);
	if (pipes->cmd_index == pipes->cmd_count - 1)
		return (STDOUT_FILENO);
	return (pipes->curr_pipe[1]);
}

void	clean_pipe(t_pipes *pipes)
{
	close_if_open(&pipes->last_read);
	close_if_open(&pipes->curr_pipe[1]);
	close_if_open(&pipes->infile);
	close_if_open(&pipes->outfile);
	pipes->last_read = pipes->curr_pipe[0];
	pipes->curr_pipe[0] = -1;
}
