/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:45:21 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 12:50:08 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_args(char **args, int i)
{
	int	count;

	count = 0;
	while (args[i] && ft_strcmp(args[i], "|"))
	{
		if ((!ft_strcmp(args[i], "<") || !ft_strcmp(args[i], ">")
				|| !ft_strcmp(args[i], ">>") || !ft_strcmp(args[i], "<<"))
			&& args[i + 1])
		{
			i += 2;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static int	handle_inout(t_cmd *cmd, char **args, int *i)
{
	if (!ft_strcmp(args[*i], "<"))
		cmd->infile = args[++(*i)];
	else if (!ft_strcmp(args[*i], ">"))
		cmd->outfile = args[++(*i)];
	else if (!ft_strcmp(args[*i], ">>"))
	{
		cmd->outfile = args[++(*i)];
		cmd->append = 1;
	}
	else if (!ft_strcmp(args[*i], "<<"))
	{
		cmd->here_doc = 1;
		cmd->limiter = args[++(*i)];
	}
	else
		return (1);
	return (0);
}

static void	free_single_cmd(void *data)
{
	t_cmd	*cmd;

	if (!data)
		return ;
	cmd = (t_cmd *)data;
	if (cmd->args)
		free(cmd->args);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->limiter)
		free(cmd->limiter);
	free(cmd);
}

void	free_cmd(t_vars *vars)
{
	if (vars->cmds)
	{
		ft_lstclear(&vars->cmds, free_single_cmd);
		vars->cmds = NULL;
	}
}

void	parse_cmd(t_vars *vars, char **args, int *i)
{
	t_cmd	*cmd;
	int		arg_i;

	cmd = init_cmd();
	if (!cmd)
		return ;
	if (count_args(args, *i))
		cmd->args = malloc(sizeof(char *) * (count_args(args, *i) + 1));
	arg_i = 0;
	while (args[*i] && ft_strcmp(args[*i], "|"))
	{
		if (handle_inout(cmd, args, i))
			cmd->args[arg_i++] = args[*i];
		(*i)++;
	}
	if (cmd->args)
		cmd->args[arg_i] = NULL;
	ft_lstadd_back(&vars->cmds, ft_lstnew(cmd));
	if (args[*i] && !ft_strcmp(args[*i], "|"))
	{
		(*i)++;
		parse_cmd(vars, args, i);
	}
}
