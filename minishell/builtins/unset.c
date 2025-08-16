/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:37:07 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 19:00:38 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_unset(char **tokens, t_vars *vars)
{
	if (!bi_is_valid(tokens, vars))
		return ;
	delete_env(vars, tokens[1]);
	vars->last_exit_code = EXIT_SUCCESS;
}
