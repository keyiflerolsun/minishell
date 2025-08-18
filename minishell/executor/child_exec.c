/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:50:08 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 12:06:31 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

static void	free_child_allocs(char **split, char *ex_path, t_vars *vars)
{
	free_split(split);
	free(ex_path);
	free_split(vars->path);
	if (vars->ep)
		free(vars->ep);
	if (vars->env)
		ft_lstclear(&vars->env, free);
	if (vars->export)
		ft_lstclear(&vars->export, free);
	if (vars->cmds)
		free_cmd(vars);
}

static void	get_name(char *cmd, char *name)
{
	int	i;

	i = -1;
	while (cmd[++i])
		name[i] = cmd[i];
	name[i] = '\0';
}

static void	execute_child(t_vars *vars, char **cmd)
{
	char	*ex_path;
	int		exec_err;
	char	name[1024];

	exec_err = -1;
	get_name(cmd[0], name);
	ex_path = get_path(vars->path, cmd[0]);
	if (ex_path)
		exec_err = execve(ex_path, cmd, vars->ep);
	free_child_allocs(cmd, ex_path, vars);
	if (exec_err)
		error_exit(name, 1);
	exit(EXIT_SUCCESS);
}

pid_t	child_exec(t_vars *vars, char **cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execute_child(vars, cmd);
	if (pid < 0)
		error_exit("fork", 1);
	return (pid);
}
