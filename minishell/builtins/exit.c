/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:38:45 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 19:54:53 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_exit(char **tokens, t_vars *vars)
{
	int	exit_code;

	if (!tokens[1])
		return (ft_clear(vars), exit(EXIT_SUCCESS));
	if (!ft_atoi(tokens[1], &exit_code))
	{
		write_err(tokens[0], "numeric argument required\n");
		return (ft_clear(vars), exit(2));
	}
	return (ft_clear(vars), exit(exit_code));
}
