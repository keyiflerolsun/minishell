/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:38:45 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 19:48:58 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	ft_ex(int exit_code, t_vars *vars)
{
	rl_clear_history();
	free(vars->ep);
	free_split(vars->path);
	ft_lstclear(&vars->env, free);
	exit(exit_code);
}

void	ft_exit(char **tokens, t_vars *vars)
{
	int	exit_code;

	if (!tokens[1])
		ft_ex(EXIT_SUCCESS, vars);
	if (!ft_atoi(tokens[1], &exit_code))
	{
		write_err(tokens[0], "numeric argument required\n");
		ft_ex(2, vars);
	}
	ft_ex(exit_code, vars);
}
