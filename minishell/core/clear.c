/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:52:32 by osancak           #+#    #+#             */
/*   Updated: 2025/08/17 12:17:23 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	ft_clear(t_vars *vars)
{
	rl_clear_history();
	if (vars->ep)
		free(vars->ep);
	if (vars->path)
		free_split(vars->path);
	if (vars->tokens)
		free_split(vars->tokens);
	if (vars->env)
		ft_lstclear(&vars->env, free);
}
