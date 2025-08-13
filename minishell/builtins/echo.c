/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:59:18 by osancak           #+#    #+#             */
/*   Updated: 2025/08/12 17:16:18 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_echo(char **tokens)
{
	char	**token;

	token = tokens + 1;
	while (*token)
	{
		write(STDOUT_FILENO, *token, ft_strlen(*token));
		write(STDOUT_FILENO, " ", 1);
		token++;
	}
	write(STDOUT_FILENO, "\n", 1);
}
