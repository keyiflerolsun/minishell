/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:45:21 by osancak           #+#    #+#             */
/*   Updated: 2025/08/29 14:37:45 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

static int	set_outfile(t_cmd *cmd, char *filename, int append)
{
	cmd->outfile = strip_quote(filename);
	cmd->append = append;
	if (!create_or_truncate(cmd->outfile, append))
		return (0);
	return (1);
}

static int	handle_inout(t_cmd *cmd, char **args, int *i)
{
	if (!is_quoted_token(args[*i]) && !ft_strcmp(args[*i], "<"))
		cmd->infile = strip_quote(args[++(*i)]);
	else if (!is_quoted_token(args[*i]) && !ft_strcmp(args[*i], ">"))
	{
		if (!set_outfile(cmd, args[++(*i)], 0))
			return (0);
	}
	else if (!is_quoted_token(args[*i]) && !ft_strcmp(args[*i], ">>"))
	{
		if (!set_outfile(cmd, args[++(*i)], 1))
			return (0);
	}
	else if (!is_quoted_token(args[*i]) && !ft_strcmp(args[*i], "<<"))
	{
		if (cmd->here_doc)
			return (2);
		cmd->infile = "here_doc";
		cmd->here_doc = 1;
		cmd->limiter = strip_quote(args[++(*i)]);
	}
	else
		return (1);
	return (0);
}

static t_cmd	*create_cmd(char **args, int *i)
{
	t_cmd	*cmd;
	int		arg_i;
	int		result;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	if (count_args(args, *i))
		cmd->args = malloc(sizeof(char *) * (count_args(args, *i) + 1));
	arg_i = 0;
	while (args[*i] && (is_quoted_token(args[*i]) || ft_strcmp(args[*i], "|")))
	{
		result = handle_inout(cmd, args, i);
		if (result == 2)
			break;
		else if (result == 1)
			cmd->args[arg_i++] = strip_quote(args[*i]);
		(*i)++;
	}
	if (cmd->args)
		cmd->args[arg_i] = NULL;
	return (cmd);
}

void	parse_cmd(t_vars *vars, char **args, int *i)
{
	t_cmd	*cmd;

	if (*args && ((ft_is_op(*args[0]) && !args[1]) || check_outfile(args)))
		return ;
	cmd = create_cmd(args, i);
	if (!cmd)
		return ;
	ft_lstadd_back(&vars->cmds, ft_lstnew(cmd));
	if (args[*i] && !is_quoted_token(args[*i]) && !ft_strcmp(args[*i], "|"))
	{
		(*i)++;
		if (!args[*i])
		{
			vars->last_exit_code = 333;
			return ;
		}
		parse_cmd(vars, args, i);
	}
	else if (args[*i] && !is_quoted_token(args[*i]) && !ft_strcmp(args[*i], "<<"))
	{
		parse_cmd(vars, args, i);
	}
}
