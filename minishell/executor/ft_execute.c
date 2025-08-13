/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:50:08 by osancak           #+#    #+#             */
/*   Updated: 2025/08/12 14:57:31 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	free_allocs(char **split, char *ex_path, char **path)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	free(ex_path);
	free_split(path);
}

pid_t	ft_execute(t_vars vars, char **cmd, char *name)
{
	pid_t	pid;
	char	*ex_path;
	int		exec_err;

	exec_err = -1;
	pid = fork();
	if (pid == 0)
	{
		ex_path = get_path(vars.path, cmd[0]);
		if (ex_path)
			exec_err = execve(ex_path, cmd, vars.ep);
		free_allocs(cmd, ex_path, vars.path);
		if (exec_err)
			error_exit(name, 1);
		exit(EXIT_SUCCESS);
	}
	if (pid < 0)
		error_exit("fork", 1);
	return (pid);
}
