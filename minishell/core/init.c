/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:43:11 by osancak           #+#    #+#             */
/*   Updated: 2025/08/31 12:40:54 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "executor.h"
#include "parser.h"

static void	env2p(t_vars *vars)
{
	t_list	*env;
	char	**ep;
	int		i;

	free(vars->ep);
	env = vars->env;
	ep = ft_calloc(sizeof(char *), ft_lstsize(env) + 1);
	i = -1;
	while (env)
	{
		ep[++i] = env->data;
		env = env->next;
	}
	vars->ep = ep;
	set_path(vars);
	vars->tmp = 0;
	static_vars(vars);
}

static void	run_prog(t_vars *vars)
{
	char	*line;

	while (1)
	{
		sort_list(vars->export);
		sort_list(vars->env);
		env2p(vars);
		if (vars->tmp != -42)
			line = readline(MAGENTA "minismet" CYAN " ¢ " RESET);
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			ft_parser(vars, ft_strtrim(line, " \t\r"));
		}
		free(line);
	}
	ft_clear();
}

void	init_shell(t_vars *vars, char **ep)
{
	setup_signals();
	vars->tmp = 0;
	vars->cmds = NULL;
	vars->tokens = NULL;
	vars->path = NULL;
	vars->ep = ft_calloc(sizeof(char *), 1);
	vars->env = NULL;
	vars->export = NULL;
	while (*ep)
	{
		ft_lstadd_back(&vars->env, ft_lstnew(ft_strdup(*ep)));
		if (ft_strstr(*ep, "_=/") && ep++)
			continue ;
		ft_lstadd_back(&vars->export, ft_lstnew(ft_strdup(*ep++)));
	}
	vars->last_exit_code = EXIT_SUCCESS;
	run_prog(vars);
}
