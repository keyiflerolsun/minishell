/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:22:16 by osancak           #+#    #+#             */
/*   Updated: 2025/08/27 08:47:10 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

int	is_quoted_token(char *token)
{
	return (token && token[0] == ARG_PIPE_SEPARATOR);
}

int	is_special_dollar(char c)
{
	if (c == '\'' || c == '"' || c == '\0' || c == ' ')
		return (1);
	return (0);
}

void	print_cmds(t_list *cmd_list)
{
	int		j;
	t_cmd	*cmd;
	t_list	*current;

	current = cmd_list;
	while (current)
	{
		cmd = (t_cmd *)current->data;
		ft_printf("Command:\n");
		if (cmd->args)
		{
			j = -1;
			while (cmd->args[++j])
				ft_printf("  arg[%d]: %s\n", j, cmd->args[j]);
		}
		if (cmd->infile)
			ft_printf("  infile: %s\n", cmd->infile);
		if (cmd->outfile)
			ft_printf("  outfile: %s (append=%d)\n", cmd->outfile, cmd->append);
		if (cmd->here_doc)
			ft_printf("  here_doc with limiter: %s\n", cmd->limiter);
		ft_printf("----\n");
		current = current->next;
	}
}

int	continus_pipe(char **token)
{
	int i;
	t_vars	*vars;

	i = 0;
	vars = static_vars(NULL);
	while (token[i])
	{
		if (token[i][0] == '|' && token[i + 1] == NULL )
		{
			vars->last_exit_code = 333;
			ft_printf("NU");
			return 1;
		}
		else if (token[i][0] == '|' && token[i + 1][0] == '|')
		{
			vars->last_exit_code = 333;
			ft_printf("BU");
			return 1;
		}
		
		
		i++;
	}
	return 0;
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
	continus_pipe(vars->tokens);
	parse_cmd(vars, vars->tokens, &i);
	print_cmds(vars->cmds);
	if (!vars->tokens)
		return (free(expanded_line));
	free(expanded_line);
	pars_to_exec(vars);
	free_cmd(vars);
}
