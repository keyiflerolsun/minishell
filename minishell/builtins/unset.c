/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:37:07 by osancak           #+#    #+#             */
/*   Updated: 2025/08/17 12:56:06 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_unset(char **tokens, t_vars *vars)
{
	if (!tokens[1])
	{
		vars->last_exit_code = EXIT_SUCCESS;
		return ;
	}
	if (*tokens[1] == '-')
	{
		write_err(tokens[0], "options are not supported\n");
		vars->last_exit_code = 42;
		return ;
	}
	delete_env(&vars->env, tokens[1]);
	delete_env(&vars->export, tokens[1]);
	vars->last_exit_code = EXIT_SUCCESS;
}
