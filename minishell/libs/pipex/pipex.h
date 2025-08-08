/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 06:40:48 by osancak           #+#    #+#             */
/*   Updated: 2025/08/08 16:26:50 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// 🧠 GNU Readline
# include <readline/history.h>  // add_history
# include <readline/readline.h> // readline, rl_*

// 🖨️ Standart IO
# include <stdio.h>  // printf, perror
# include <string.h> // strerror

// 🧠 Memory
# include <stdlib.h> // malloc, free, exit, getenv

// 🔧 Sys Calls
# include <fcntl.h>     // open
# include <sys/stat.h>  // stat, lstat, fstat, unlink
# include <sys/types.h> // stat yapıları
// write, access, read, close, fork, execve, dup*, pipe, isatty, tty*
# include <unistd.h>

// 🧒 Processes
# include <errno.h>    // errno
# include <signal.h>   // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/wait.h> // wait, waitpid, wait3, wait4

// 📂 *dir
# include <dirent.h> // opendir, readdir, closedir

// 🧭 Cwd
# include <unistd.h> // getcwd, chdir

// 🖥️ Terminal Control
# include <sys/ioctl.h> // ioctl
# include <unistd.h>    // isatty, ttyname, ttyslot

// 🧵 Terminal Attr
# include <termios.h> // tcgetattr, tcsetattr

// 🧾 Termcap
# include <termcap.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

// pipex
# include "get_next_line.h"

# ifndef MAX_PIPE
#  define MAX_PIPE 512
# endif

typedef struct s_pipe
{
	int		infile;
	int		outfile;
	int		curr_pipe[2];
	int		last_read;
	char	**path;
	pid_t	cmds[MAX_PIPE];
	int		exit_codes[MAX_PIPE];
	int		cmd_count;
	int		cmd_index;
}			t_pipe;

int			check_args(char **argv);
void		error_exit(const char *msg, int exit_code);
void		set_path(t_pipe *vars, char **envp);
char		*get_path(char **path, char *command);
void		free_path(char **path);
void		init_vars(t_pipe *vars, char *input_file, char *output_file);
void		close_fd(t_pipe vars);
pid_t		ft_cmd(t_pipe vars, char *command, char **envp);
void		setup_pipe(t_pipe *vars);
int			get_pipe_in(t_pipe *vars);
int			get_pipe_out(t_pipe *vars);
void		clean_pipe(t_pipe *vars);
pid_t		ft_heredot(char *limiter);
int			exec_prog(t_pipe *vars, int argc, char **argv, char **envp);

#endif
