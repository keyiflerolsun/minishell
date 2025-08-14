/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:22:16 by osancak           #+#    #+#             */
/*   Updated: 2025/08/14 18:03:04 by osancak          ###   ########.fr       */
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

void	ft_parser(t_vars *vars, char *line)
{
	char	**tokens;
	char	*temp;
	int		i;

	if (!line || !*line)
		return (free(line));
	tokens = quote_aware_split(line);
	if (!tokens)
		return (free(line));
	free(line);
	i = -1;
	while (tokens[++i])
	{
		temp = tokens[i];
		tokens[i] = process_token(tokens[i]);
		printf("%s»» TOKEN [%d]: %s%10s%s » %s%-20s\n",
			BOLD_GREEN, i, BLUE, temp,
			YELLOW, tokens[i], RESET);
		free(temp);
	}
	if (!is_builtin(vars, tokens))
		waitpid(ft_execute(*vars, tokens), NULL, 0);
	free_split(tokens);
}
