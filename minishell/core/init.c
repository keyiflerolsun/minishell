/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:43:11 by osancak           #+#    #+#             */
/*   Updated: 2025/08/09 14:51:41 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "executor.h"

static void	run_prog(t_vars *vars)
{
	char	*line;

	while (1)
	{
		line = readline(MAGENTA "minismet" BLUE " ¢ " RESET);
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			waitpid(ft_execute(*vars, line), NULL, 0);
		}
		free(line);
	}
	rl_clear_history();
	free_path(vars->path);
	printf("\n\n" RED "exit" RESET "\n\n");
}

void	init_shell(t_vars *vars, char **ep)
{
	setup_signals();
	vars->ep = ep;
	set_path(vars);
	run_prog(vars);
}
