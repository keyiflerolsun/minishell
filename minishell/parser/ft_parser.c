/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:22:16 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 12:09:29 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

void	print_cmds(t_cmd *cmd)
{
	int	j;

	while (cmd)
	{
		printf("Command:\n");
		if (cmd->args)
		{
			j = 0;
			while (cmd->args[j])
			{
				printf("  arg[%d]: %s\n", j, cmd->args[j]);
				j++;
			}
		}
		if (cmd->infile)
			printf("  infile: %s\n", cmd->infile);
		if (cmd->outfile)
			printf("  outfile: %s (append=%d)\n", cmd->outfile, cmd->append);
		if (cmd->here_doc)
			printf("  here_doc with limiter: %s\n", cmd->limiter);
		printf("----\n");
		cmd = cmd->next_cmd;
	}
}

void	ft_parser(t_vars *vars, char *line)
{
	char	*expanded_line;
	int		i;

	i = 0;
	if (!line || !*line)
		return (free(line));
	expanded_line = expand_env(*vars, line);
	free(line);
	if (vars->tokens)
		free_split(vars->tokens);
	vars->tokens = quote_aware_split(expanded_line);
	vars->cmds = parse_cmd(vars->tokens, &i);
	print_cmds(vars->cmds);
	if (!vars->tokens)
		return (free(expanded_line));
	free(expanded_line);
	pars_to_exec(vars);
	free_cmd(vars);
}
