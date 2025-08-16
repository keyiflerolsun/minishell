/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:44:32 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 16:56:57 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_directory_access(char *path)
{
	struct stat	statbuf;

	if (!path)
		return (0);
	if (stat(path, &statbuf) != 0)
	{
		write_err(path, "No such file or directory\n");
		return (0);
	}
	if (!S_ISDIR(statbuf.st_mode))
	{
		write_err(path, "Not a directory\n");
		return (0);
	}
	if (access(path, R_OK | X_OK) != 0)
	{
		write_err(path, "Permission denied\n");
		return (0);
	}
	return (1);
}

void	ft_cd(char **tokens, t_vars *vars)
{
	char	*old;

	if (tokens[2])
	{
		write_err("cd", "options or arguments are not supported\n");
		vars->last_exit_code = EXIT_FAILURE;
		return ;
	}
	if (!tokens[1] || !check_directory_access(tokens[1]))
	{
		vars->last_exit_code = EXIT_FAILURE;
		return ;
	}
	if (chdir(tokens[1]) != 0)
	{
		write_err("cd", "Failed to change directory\n");
		vars->last_exit_code = EXIT_FAILURE;
		return ;
	}
	old = get_env(*vars, "PWD");
	update_env(vars, "OLDPWD", old);
	free(old);
	update_env(vars, "PWD", tokens[1]);
	vars->last_exit_code = EXIT_SUCCESS;
}
