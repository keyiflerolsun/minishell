/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:38:58 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 16:32:41 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	fd_apply(t_pipes *pipes)
{
	dup2(get_pipe_in(pipes), STDIN_FILENO);
	dup2(get_pipe_out(pipes), STDOUT_FILENO);
}

void	close_fd(t_pipes pipes)
{
	if (pipes.curr_pipe[0] > 2)
		close(pipes.curr_pipe[0]);
	if (pipes.curr_pipe[1] > 2)
		close(pipes.curr_pipe[1]);
	if (pipes.last_read > 2)
		close(pipes.last_read);
	if (pipes.infile > 2)
		close(pipes.infile);
	if (pipes.outfile > 2)
		close(pipes.outfile);
}
