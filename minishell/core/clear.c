/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:52:32 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 12:06:31 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "parser.h"

void	ft_clear(t_vars *vars)
{
	rl_clear_history();
	free_split(vars->path);
	free_split(vars->tokens);
	if (vars->ep)
		free(vars->ep);
	if (vars->env)
		ft_lstclear(&vars->env, free);
	if (vars->export)
		ft_lstclear(&vars->export, free);
	if (vars->cmds)
		free_cmd(vars);
}
