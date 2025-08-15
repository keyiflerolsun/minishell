/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:43:11 by osancak           #+#    #+#             */
/*   Updated: 2025/08/15 19:32:51 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "executor.h"
#include "parser.h"

static void	run_prog(t_vars *vars)
{
	char	*line;

	while (1)
	{
		line = readline(MAGENTA "minismet" CYAN " ¢ " RESET);
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			ft_parser(vars, ft_strtrim(line, " "));
		}
		free(line);
	}
	rl_clear_history();
	free_split(vars->path);
	ft_lstclear(&vars->envs, free);
	ft_printf("\n\n" RED "exit" RESET "\n\n");
}

void	init_shell(t_vars *vars, char **ep)
{
	setup_signals();
	vars->ep = ep;
	vars->envs = NULL;
	while (*ep)
		ft_lstadd_back(&vars->envs, ft_lstnew(ft_strdup(*ep++)));
	vars->last_exit_code = EXIT_SUCCESS;
	set_path(vars);
	run_prog(vars);
}
