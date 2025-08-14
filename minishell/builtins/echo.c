/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:59:18 by osancak           #+#    #+#             */
/*   Updated: 2025/08/14 12:34:46 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	is_env(char *token, t_vars vars)
{
	char	**ep;
	int		t_len;

	ep = vars.ep;
	t_len = ft_strlen(token);
	if (*token != '$')
		write(STDOUT_FILENO, token, t_len);
	else
	{
		token++;
		t_len--;
		while (*ep)
		{
			if (!ft_strncmp(*ep, token, t_len))
			{
				*ep += t_len + 1;
				write(STDOUT_FILENO, *ep, ft_strlen(*ep));
			}
			ep++;
		}
	}
}

void	ft_echo(char **tokens, t_vars vars)
{
	char	**token;
	int		new_line;

	token = tokens + 1;
	if (!*token)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (!ft_strncmp(*token, "-n", 2))
	{
		new_line = 0;
		token++;
	}
	else
		new_line = 1;
	while (*token)
	{
		is_env(*token, vars);
		if (*(token + 1))
			write(STDOUT_FILENO, " ", 1);
		token++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
}
