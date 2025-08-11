/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:22:16 by osancak           #+#    #+#             */
/*   Updated: 2025/08/11 16:08:07 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "parser.h"

void	ft_parser(t_vars *vars, char *line)
{
	char	**tokens;
	char	*proc;
	int		i;

	tokens = quote_aware_split(line);
	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		proc = process_token(tokens[i]);
		printf("Original: %s : TOKEN [%i]: %s\n", tokens[i], i, proc);
		free(proc);
		free(tokens[i]);
		i++;
	}
	free(tokens);
	if (!ft_strncmp(line, "pwd", 3))
		ft_pwd(line);
	else if (!ft_strncmp(line, "env", 3))
		ft_env(line, *vars);
	else
		waitpid(ft_execute(*vars, line), NULL, 0);
}
