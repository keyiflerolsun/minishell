/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:24:32 by osancak           #+#    #+#             */
/*   Updated: 2025/09/01 10:59:28 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"

static void	fds_backup_and_apply(t_pipes *pipes, int *backup_fds)
{
	int	pipe_in;
	int	pipe_out;

	backup_fds[0] = -1;
	backup_fds[1] = -1;
	pipe_in = get_pipe_in(pipes);
	pipe_out = get_pipe_out(pipes);
	if (pipe_in != STDIN_FILENO)
	{
		backup_fds[0] = dup(STDIN_FILENO);
		dup2(pipe_in, STDIN_FILENO);
	}
	if (pipe_out != STDOUT_FILENO)
	{
		backup_fds[1] = dup(STDOUT_FILENO);
		dup2(pipe_out, STDOUT_FILENO);
	}
}

static void	fds_restore_and_close(int *backup_fds)
{
	if (backup_fds[0] != -1)
	{
		dup2(backup_fds[0], STDIN_FILENO);
		close(backup_fds[0]);
	}
	if (backup_fds[1] != -1)
	{
		dup2(backup_fds[1], STDOUT_FILENO);
		close(backup_fds[1]);
	}
}

int	builtin_exec(t_vars *vars, t_pipes *pipes, char **cmd)
{
	int	backup_fds[2];

	fds_backup_and_apply(pipes, backup_fds);
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
		ft_exit(vars, cmd, pipes->cmd_count);
	else
		return (fds_restore_and_close(backup_fds), 0);
	return (fds_restore_and_close(backup_fds), 1);
}
