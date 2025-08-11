/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:22:16 by osancak           #+#    #+#             */
/*   Updated: 2025/08/11 16:50:11 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "parser.h"

void	ft_parser(t_vars *vars, char *line)
{
	char	**tokens;
	int		i;
	char	*temp;
	char	*name;

	tokens = quote_aware_split(line);
	if (!tokens)
		return ;
	i = -1;
	while (tokens[++i])
	{
		temp = tokens[i];
		tokens[i] = process_token(tokens[i]);
		printf("TOKEN [%i]: %s\n", i, tokens[i]);
		free(temp);
	}
	name = ft_strdup(tokens[0]);
	if (!ft_strncmp(*tokens, "pwd", 3))
		ft_pwd(*tokens);
	else if (!ft_strncmp(*tokens, "env", 3))
		ft_env(*tokens, *vars);
	else
		waitpid(ft_execute(*vars, tokens, name), NULL, 0);
	free(tokens);
	free(name);
}
