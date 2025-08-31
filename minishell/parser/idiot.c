/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idiot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:17:56 by hyakici           #+#    #+#             */
/*   Updated: 2025/08/31 19:33:54 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_is_outfile(char c)
{
	if (c == '>')
		return (1);
	return (0);
}

int	ft_is_op(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	cont_meta(t_vars *vars, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_is_op(args[i][0])
			&& (!args[i + 1] || ft_is_outfile(args[i + 1][0])))
		{
			vars->last_exit_code = 333;
			return (1);
		}
		i++;
	}
	return (0);
}
