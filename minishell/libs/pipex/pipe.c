/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 07:38:23 by osancak           #+#    #+#             */
/*   Updated: 2025/08/08 16:26:50 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_pipe(t_pipe *vars)
{
	if (vars->cmd_index != vars->cmd_count)
		if (pipe(vars->curr_pipe) == -1)
			error_exit("pipe", 1);
}

int	get_pipe_in(t_pipe *vars)
{
	return (vars->last_read);
}

int	get_pipe_out(t_pipe *vars)
{
	if (vars->cmd_index == vars->cmd_count)
		return (vars->outfile);
	return (vars->curr_pipe[1]);
}

void	clean_pipe(t_pipe *vars)
{
	close(vars->last_read);
	close(vars->curr_pipe[1]);
	vars->last_read = vars->curr_pipe[0];
}
