/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:50:08 by osancak           #+#    #+#             */
/*   Updated: 2025/08/31 12:37:59 by osancak          ###   ########.fr       */
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

void	ex_execve(t_vars *vars, t_pipes *pipes, char **cmd)
{
	char	*ex_path;
	int		exec_err;
	char	name[1024];

	exec_err = -1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	get_name(cmd[0], name);
	fd_apply(pipes);
	close_fd(pipes);
	ex_path = get_path(vars->path, cmd[0]);
	if (ex_path)
		exec_err = execve(ex_path, cmd, vars->ep);
	free(ex_path);
	ft_clear();
	if (exec_err)
		error_exit(name, NULL);
	exit(EXIT_SUCCESS);
}
