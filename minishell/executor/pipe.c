/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 07:38:23 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 16:31:19 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	setup_pipe(t_pipes *pipes)
{
	pipes->infile = STDIN_FILENO;
	pipes->outfile = STDOUT_FILENO;
	if (pipes->cmd_index != pipes->cmd_count)
		if (pipe(pipes->curr_pipe) == -1)
			error_exit("pipe", 1);
}

int	get_pipe_in(t_pipes *pipes)
{
	return (pipes->last_read);
}

int	get_pipe_out(t_pipes *pipes)
{
	if (pipes->cmd_index == pipes->cmd_count)
		return (pipes->outfile);
	return (pipes->curr_pipe[1]);
}

void	clean_pipe(t_pipes *pipes)
{
	close(pipes->last_read);
	close(pipes->curr_pipe[1]);
	pipes->last_read = pipes->curr_pipe[0];
}
