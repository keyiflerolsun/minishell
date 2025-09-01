/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:41:18 by osancak           #+#    #+#             */
/*   Updated: 2025/09/01 15:34:23 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"

static void	ft_errno_manipulate(t_vars *vars, int ex, char *left)
{
	if (ex == 127)
	{
		write_err(left, "Command not found\n");
		exit(ex);
	}
	if (ex == ENOENT)
	{
		vars->last_exit_code = 127;
		write_err(left, "No such file or directory\n");
		exit(vars->last_exit_code);
	}
	if (ex == EACCES)
	{
		vars->last_exit_code = 126;
		write_err(left, "Is a directory\n");
		exit(vars->last_exit_code);
	}
	if (ex == ENOTDIR)
		vars->last_exit_code = 126;
}

void	error_exit(char *left, char *right)
{
	t_vars	*vars;

	vars = static_vars(NULL);
	vars->last_exit_code = errno;
	ft_errno_manipulate(vars, vars->last_exit_code, left);
	if (!right)
		write_perr(left);
	else
		write_err(left, right);
	exit(vars->last_exit_code);
}
