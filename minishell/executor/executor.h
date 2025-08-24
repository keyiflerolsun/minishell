/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:08:19 by osancak           #+#    #+#             */
/*   Updated: 2025/08/24 13:01:10 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "core.h"

# ifndef MAX_PIPE
#  define MAX_PIPE 512
# endif

typedef struct s_pipes
{
	int		infile;
	int		outfile;
	int		curr_pipe[2];
	int		last_read;
	pid_t	cmds[MAX_PIPE];
	int		exit_codes[MAX_PIPE];
	t_list	*cmd_list;
	int		cmd_count;
	int		cmd_index;
}			t_pipes;

void		error_exit(const char *msg, int exit_code);
int			builtin_exec(t_vars *vars, t_pipes *pipes, char **cmd);
pid_t		child_exec(t_vars *vars, t_pipes *pipes, char **cmd);
void		pars_to_exec(t_vars *vars);
void		init_infile(t_pipes *pipes);
void		init_outfile(t_pipes *pipes);
void		setup_pipe(t_pipes *pipes);
int			get_pipe_in(t_pipes *pipes);
int			get_pipe_out(t_pipes *pipes);
void		clean_pipe(t_pipes *pipes);
void		fd_apply(t_pipes *pipes);
void		close_fd(t_pipes pipes);
void		ft_heredot(t_vars *vars, char *limiter);
void		ft_wait_pid(t_vars *vars, pid_t pid, void (*prev_sigint)(int));

#endif
