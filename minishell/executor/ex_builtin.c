/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:24:32 by osancak           #+#    #+#             */
/*   Updated: 2025/09/02 11:01:03 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"

int	ft_is_builtin(char **cmd)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	return (0);
}

void	fds_backup_and_apply(t_pipes *pipes, int *backup_fds)
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

void	fds_restore_and_close(int *backup_fds)
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

int	bi_exec(t_vars *vars, t_pipes *pipes, char **cmd)
{
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
	return (0);
}

void	ex_builtin(t_vars *vars, t_pipes *pipes, char **cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	fd_apply(pipes);
	close_fd(pipes);
	bi_exec(vars, pipes, cmd);
	ft_clear();
	exit(vars->last_exit_code);
}
