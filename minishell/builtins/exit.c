/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:38:45 by osancak           #+#    #+#             */
/*   Updated: 2025/08/31 19:29:00 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"

void	ft_exit(char **tokens, int cmd_count)
{
	int	exit_code;

	if (cmd_count > 1)
		return ;
	if (!tokens[1])
		return (ft_clear(), exit(EXIT_SUCCESS));
	if (!ft_atoi(tokens[1], &exit_code))
	{
		write_err(tokens[1], "numeric argument required\n");
		return (ft_clear(), exit(2));
	}
	if (tokens[2])
	{
		write_err(tokens[0], "too many arguments\n");
		return ;
	}
	return (ft_clear(), exit(exit_code));
}
