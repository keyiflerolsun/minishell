/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:22:16 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 14:40:51 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "parser.h"

static int	is_builtin(t_vars *vars, char **tokens)
{
	if (!ft_strncmp(*tokens, "pwd", 3))
		return (ft_pwd(*tokens), 1);
	else if (!ft_strncmp(*tokens, "env", 3))
		return (ft_env(*tokens, *vars), 1);
	else if (!ft_strncmp(*tokens, "echo", 4))
		return (ft_echo(tokens, *vars), 1);
	return (0);
}

static void	check_dollar(t_vars vars, char **tokens)
{
	int		i;
	char	*tmp;

	i = -1;
	while (tokens[++i])
	{
		if (ft_strchr(tokens[i], '$'))
		{
			tmp = get_env(vars, tokens[i]);
			free(tokens[i]);
			tokens[i] = tmp;
		}
		printf("%s»» TOKEN [%d]: %s%10s » %s%-20s\n",
			BOLD_GREEN, i, BLUE,
			YELLOW, tokens[i], RESET);
	}
}

void	ft_parser(t_vars *vars, char *line)
{
	char	**tokens;

	if (!line || !*line)
		return (free(line));
	tokens = quote_aware_split(line);
	if (!tokens)
		return (free(line));
	free(line);
	check_dollar(*vars, tokens);
	if (!is_builtin(vars, tokens))
	{
		waitpid(ft_execute(*vars, tokens), &vars->last_exit_code, 0);
		if (WIFEXITED(vars->last_exit_code))
			vars->last_exit_code = WEXITSTATUS(vars->last_exit_code);
		else
			vars->last_exit_code = EXIT_FAILURE;
	}
	free_split(tokens);
}
