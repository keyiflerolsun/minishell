/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:40:13 by osancak           #+#    #+#             */
/*   Updated: 2025/08/08 16:26:50 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	run_prog(t_pipe *vars, char **cmds, char **envp)
{
	int	i;
	int	exit_status;

	i = -1;
	while (++i <= vars->cmd_count)
	{
		vars->cmd_index = i;
		setup_pipe(vars);
		vars->cmds[i] = ft_cmd(*vars, cmds[i], envp);
		clean_pipe(vars);
	}
	close_fd(*vars);
	free_path(vars->path);
	i = -1;
	while (++i <= vars->cmd_count)
	{
		waitpid(vars->cmds[i], &exit_status, 0);
		vars->exit_codes[i] = WEXITSTATUS(exit_status);
	}
}

int	exec_prog(t_pipe *vars, int argc, char **argv, char **envp)
{
	if (!ft_strstr(argv[1], "here_doc"))
	{
		vars->cmd_count = argc - 4;
		run_prog(vars, argv + 2, envp);
	}
	else
	{
		vars->cmd_count = argc - 5;
		run_prog(vars, argv + 3, envp);
		unlink("here_doc");
	}
	if (access(argv[argc - 1], W_OK) == 0)
		return (vars->exit_codes[vars->cmd_count]);
	return (EXIT_FAILURE);
}
