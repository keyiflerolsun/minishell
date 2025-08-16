/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:37:07 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 16:39:11 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_unset(char **tokens, t_vars *vars)
{
	if (tokens[2])
	{
		write_err("unset", "options or arguments are not supported\n");
		vars->last_exit_code = EXIT_FAILURE;
		return ;
	}
	delete_env(vars, tokens[1]);
	vars->last_exit_code = EXIT_SUCCESS;
}
