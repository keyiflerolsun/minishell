/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:24:32 by osancak           #+#    #+#             */
/*   Updated: 2025/08/24 15:43:37 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"

static void	fds_backup_and_apply(t_pipes *pipes, int *fds)
{
	fds[0] = -1;
	fds[1] = -1;
	if (get_pipe_in(pipes) != STDIN_FILENO)
	{
		fds[0] = dup(STDIN_FILENO);
		dup2(get_pipe_in(pipes), STDIN_FILENO);
	}
	if (get_pipe_out(pipes) != STDOUT_FILENO)
	{
		fds[1] = dup(STDOUT_FILENO);
		dup2(get_pipe_out(pipes), STDOUT_FILENO);
	}
}

static void	fds_restore_and_close(int *fds)
{
	if (fds[0] != -1)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	if (fds[1] != -1)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
}

int	builtin_exec(t_vars *vars, t_pipes *pipes, char **cmd)
{
	int	fds[2];

	fds_backup_and_apply(pipes, fds);
	if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd(cmd, vars);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(cmd, vars);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd, vars);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd, vars);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd, vars);
	else if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(cmd, vars);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(cmd);
	else
		return (fds_restore_and_close(fds), 0);
	return (fds_restore_and_close(fds), 1);
}
