/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:19 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 13:02:18 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "core.h"

# ifndef MAX_PIPE
#  define MAX_PIPE 512
# endif

typedef struct s_pipe
{
	int		curr_pipe[2];
	int		last_read;
	pid_t	cmds[MAX_PIPE];
	int		exit_codes[MAX_PIPE];
	int		cmd_count;
	int		cmd_index;
}			t_pipe;

void		error_exit(const char *msg, int exit_code);
int			builtin_exec(t_vars *vars, char **cmd);
pid_t		child_exec(t_vars *vars, char **cmd);
void		pars_to_exec(t_vars *vars);

#endif
