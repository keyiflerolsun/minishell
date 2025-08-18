/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:04:29 by osancak           #+#    #+#             */
/*   Updated: 2025/08/18 14:33:04 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

void	init_infile(t_pipes *pp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)pp->cmd_list->data;
	pp->infile = open(cmd->infile, O_RDONLY);
	if (pp->infile < 0)
	{
		error_exit(cmd->infile, 42);
		pp->infile = open("/dev/null", O_CREAT | O_RDWR | O_TRUNC);
	}
}

void	init_outfile(t_pipes *pp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)pp->cmd_list->data;
	if (cmd->append)
		pp->outfile = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		pp->outfile = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pp->outfile < 0)
	{
		error_exit(cmd->outfile, 42);
		pp->outfile = open("/dev/null", O_CREAT | O_RDWR | O_TRUNC);
	}
}
