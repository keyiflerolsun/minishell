/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:50:08 by osancak           #+#    #+#             */
/*   Updated: 2025/08/28 16:38:19 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

static void	get_name(char *cmd, char *name)
{
	int	i;

	i = -1;
	while (cmd[++i])
		name[i] = cmd[i];
	name[i] = '\0';
}

static void	execute_child(t_vars *vars, t_pipes *pipes, char **cmd)
{
	char	*ex_path;
	int		exec_err;
	char	name[1024];

	exec_err = -1;
	get_name(cmd[0], name);
	fd_apply(pipes);
	close_fd(*pipes);
	ex_path = get_path(vars->path, cmd[0]);
	if (ex_path)
		exec_err = execve(ex_path, cmd, vars->ep);
	free(ex_path);
	ft_clear();
	if (exec_err)
		error_exit(name, NULL);
	exit(EXIT_SUCCESS);
}

void	child_exec(t_vars *vars, t_pipes *pipes, char **cmd)
{
	pid_t			pid;
	__sighandler_t	signals[2];

	signals[0] = signal(SIGINT, SIG_IGN);
	signals[1] = signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		execute_child(vars, pipes, cmd);
	if (pid < 0)
		error_exit("child_exec » fork", NULL);
	ft_wait_pid(vars, pid);
	signal(SIGINT, signals[0]);
	signal(SIGQUIT, signals[1]);
}
