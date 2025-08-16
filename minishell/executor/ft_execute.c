/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:50:08 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 15:00:44 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	free_allocs(char **split, char *ex_path, t_vars *vars)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	free(ex_path);
	free_split(vars->path);
	ft_lstclear(&vars->env, free);
	free(vars->ep);
}

static void	get_name(char *cmd, char *name)
{
	int	i;

	i = -1;
	while (cmd[++i])
		name[i] = cmd[i];
	name[i] = '\0';
}

pid_t	ft_execute(t_vars vars, char **cmd)
{
	pid_t	pid;
	char	*ex_path;
	int		exec_err;
	char	name[1024];

	exec_err = -1;
	pid = fork();
	if (pid == 0)
	{
		get_name(cmd[0], name);
		ex_path = get_path(vars.path, cmd[0]);
		if (ex_path)
			exec_err = execve(ex_path, cmd, vars.ep);
		free_allocs(cmd, ex_path, &vars);
		if (exec_err)
			error_exit(name, 1);
		exit(EXIT_SUCCESS);
	}
	if (pid < 0)
		error_exit("fork", 1);
	return (pid);
}
