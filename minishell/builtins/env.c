/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:48:54 by osancak           #+#    #+#             */
/*   Updated: 2025/08/11 15:27:39 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(char *line, t_vars vars)
{
	char	**ep;

	if (ft_strlen(line) != 3)
	{
		write_err("env", "options or arguments are not supported\n");
		return ;
	}
	ep = vars.ep;
	while (*ep)
		printf("%s\n", *ep++);
}
