/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:45:21 by osancak           #+#    #+#             */
/*   Updated: 2025/08/23 17:03:08 by osancak          ###   ########.fr       */
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

static int	create_or_truncate(char *filename, int append)
{
	int	fd;

	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	handle_inout(t_cmd *cmd, char **args, int *i)
{
	if (!ft_strcmp(args[*i], "<"))
		cmd->infile = args[++(*i)];
	else if (!ft_strcmp(args[*i], ">"))
	{
		cmd->outfile = args[++(*i)];
		if (!create_or_truncate(cmd->outfile, 0))
			return (0);
		cmd->append = 0;
	}
	else if (!ft_strcmp(args[*i], ">>"))
	{
		cmd->outfile = args[++(*i)];
		if (!create_or_truncate(cmd->outfile, 1))
			return (0);
		cmd->append = 1;
	}
	else if (!ft_strcmp(args[*i], "<<"))
	{
		cmd->infile = "here_doc";
		cmd->here_doc = 1;
		cmd->limiter = args[++(*i)];
	}
	else
		return (1);
	return (0);
}

static t_cmd	*create_cmd(char **args, int *i)
{
	t_cmd	*cmd;
	int		arg_i;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
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
	return (cmd);
}

void	parse_cmd(t_vars *vars, char **args, int *i)
{
	t_cmd	*cmd;

	cmd = create_cmd(args, i);
	if (!cmd)
		return ;
	ft_lstadd_back(&vars->cmds, ft_lstnew(cmd));
	if (args[*i] && !ft_strcmp(args[*i], "|"))
	{
		(*i)++;
		if (!args[*i])
		{
			vars->last_exit_code = 333;
			return ;
		}
		parse_cmd(vars, args, i);
	}
}
