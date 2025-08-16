/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:22:16 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 15:34:22 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "parser.h"

static int	is_builtin(t_vars *vars, char **tokens)
{
	if (!ft_strncmp(*tokens, "pwd\0", 4))
		return (ft_pwd(tokens, vars), 1);
	else if (!ft_strncmp(*tokens, "env\0", 4))
		return (ft_env(tokens, vars), 1);
	else if (!ft_strncmp(*tokens, "echo\0", 5))
		return (ft_echo(tokens, *vars), 1);
	else if (!ft_strncmp(*tokens, "export\0", 7))
		return (ft_export(tokens, vars), 1);
	return (0);
}

void	ft_parser(t_vars *vars, char *line)
{
	char	**tokens;
	char	*expanded_line;

	if (!line || !*line)
		return (free(line));
	expanded_line = expand_env(line, vars->ep);
	free(line);
	tokens = quote_aware_split(expanded_line);
	if (!tokens)
		return (free(expanded_line));
	free(expanded_line);
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
