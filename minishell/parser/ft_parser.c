/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:22:16 by osancak           #+#    #+#             */
/*   Updated: 2025/08/11 14:55:09 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "parser.h"

void	ft_parser(t_vars *vars, char *line)
{
	if (ft_strlen(line) == 3)
	{
		if (!ft_strncmp(line, "pwd", 3))
			ft_pwd();
		else if (!ft_strncmp(line, "env", 3))
			ft_env(*vars);
		else
			waitpid(ft_execute(*vars, line), NULL, 0);
	}
	else
		waitpid(ft_execute(*vars, line), NULL, 0);
}
