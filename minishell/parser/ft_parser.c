/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:22:16 by osancak           #+#    #+#             */
/*   Updated: 2025/08/17 15:04:13 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "parser.h"

static int	is_builtin(t_vars *vars, char **tokens)
{
	if (!ft_strcmp(*tokens, "pwd"))
		return (ft_pwd(tokens, vars), 1);
	else if (!ft_strcmp(*tokens, "env"))
		return (ft_env(tokens, vars), 1);
	else if (!ft_strcmp(*tokens, "echo"))
		return (ft_echo(tokens, vars), 1);
	else if (!ft_strcmp(*tokens, "export"))
		return (ft_export(tokens, vars), 1);
	else if (!ft_strcmp(*tokens, "unset"))
		return (ft_unset(tokens, vars), 1);
	else if (!ft_strcmp(*tokens, "cd"))
		return (ft_cd(tokens, vars), 1);
	else if (!ft_strcmp(*tokens, "exit"))
		return (ft_exit(tokens, vars), 1);
	return (0);
}

void	print_cmds(t_cmd *cmd)
{
	int	j;

	while (cmd)
	{
		printf("Command:\n");
		if (cmd->cmd_args)
		{
			j = 0;
			while (cmd->cmd_args[j])
			{
				printf("  arg[%d]: %s\n", j, cmd->cmd_args[j]);
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

static void	ft_to_exec(t_vars *vars)
{
	if (!is_builtin(vars, vars->tokens))
	{
		waitpid(ft_execute(*vars, vars->tokens), &vars->last_exit_code, 0);
		if (WIFEXITED(vars->last_exit_code))
			vars->last_exit_code = WEXITSTATUS(vars->last_exit_code);
		else
			vars->last_exit_code = EXIT_FAILURE;
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
	vars->cmd_info = parse_cmd(vars->tokens, &i);
	print_cmds(vars->cmd_info);
	if (!vars->tokens)
		return (free(expanded_line));
	free(expanded_line);
	ft_to_exec(vars);
	free_cmd(vars->cmd_info);
}
