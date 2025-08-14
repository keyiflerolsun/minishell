/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:59:18 by osancak           #+#    #+#             */
/*   Updated: 2025/08/14 20:28:37 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_env(char *token, char **ep)
{
	char	*tmp;
	int		i;

	i = 0;
	while (token[i] && token[i] != '$')
		i++;
	token[i] = '\0';
	tmp = ft_strjoin(token, "=");
	while (*ep)
	{
		if (!ft_strncmp(*ep, tmp, ft_strlen(tmp)))
		{
			ft_printf("%s", *ep + ft_strlen(tmp));
			break ;
		}
		ep++;
	}
	free(tmp);
	token[i] = '$';
}

static void	echo_string(char *token, t_vars vars)
{
	while (*token)
	{
		if (*token == '$' && token++)
		{
			if (*token == '?' && token++)
				ft_printf("hayırdır ingiltere prensiyle mi konuşuyorum?");
			else if (*token == '$' && token++)
				ft_printf("%d", getpid());
			else if (*token == '0' && token++)
				ft_printf("minismet");
			else
			{
				print_env(token, vars.ep);
				while (*token && *token != '$')
					token++;
			}
		}
		else
			ft_printf("%c", *token++);
	}
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
			ft_printf(" ");
		args++;
	}
	if (print_newline)
		ft_printf("\n");
}
