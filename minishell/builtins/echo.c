/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:59:18 by osancak           #+#    #+#             */
/*   Updated: 2025/08/14 14:03:02 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_env(char *token, char **ep)
{
	char	*tmp;

	tmp = ft_strjoin(token, "=");
	while (*ep)
	{
		if (!ft_strncmp(*ep, tmp, ft_strlen(tmp)))
			printf("%s", *ep + ft_strlen(tmp));
		ep++;
	}
	free(tmp);
}

static void	echo_string(char *token, t_vars vars)
{
	if (*token == '$')
	{
		if (*(token + 1) == '?' && token++)
		{
			printf("hayırdır ingiltere prensiyle mi konuşuyorum?");
			if (++token)
				printf("%s", token);
		}
		else if (*(token + 1) == '$' && token++)
		{
			printf("sen güzel bir kardeşe benziyorsun.");
			if (++token)
				printf("%s", token);
		}
		else
			print_env(++token, vars.ep);
	}
	else
		write(STDOUT_FILENO, token, ft_strlen(token));
}

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
	while (*args && n_is_valid(*args) && args++)
		print_newline = 0;
	while (*args)
	{
		echo_string(*args, vars);
		if (*(args + 1))
			write(STDOUT_FILENO, " ", 1);
		args++;
	}
	if (print_newline)
		printf("\n");
}
