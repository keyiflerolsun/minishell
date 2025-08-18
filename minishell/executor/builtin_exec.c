/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:24:32 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 12:00:29 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"

int	builtin_exec(t_vars *vars, char **cmd)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd(cmd, vars), 1);
	else if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(cmd, vars), 1);
	else if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo(cmd, vars), 1);
	else if (!ft_strcmp(cmd[0], "export"))
		return (ft_export(cmd, vars), 1);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (ft_unset(cmd, vars), 1);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (ft_cd(cmd, vars), 1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (ft_exit(cmd, vars), 1);
	return (0);
}
