/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:59:18 by osancak           #+#    #+#             */
/*   Updated: 2025/08/15 17:04:29 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	n_is_valid(char *arg)
{
	if (!arg || *arg++ != '-' || *arg++ != 'n')
		return (0);
	while (*arg)
	{
		if (*arg++ != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo(char **tokens, t_vars vars)
{
	char	**args;
	int		print_newline;

	args = tokens + 1;
	print_newline = 1;
	(void)vars;
	while (*args && n_is_valid(*args) && args++)
		print_newline = 0;
	while (*args)
	{
		ft_printf("%s", *args);
		if (*(args + 1))
			ft_printf(" ");
		args++;
	}
	if (print_newline)
		ft_printf("\n");
}
