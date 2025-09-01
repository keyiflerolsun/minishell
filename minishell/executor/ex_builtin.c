/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:24:32 by osancak           #+#    #+#             */
/*   Updated: 2025/09/01 17:22:07 by osancak          ###   ########.fr       */
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
