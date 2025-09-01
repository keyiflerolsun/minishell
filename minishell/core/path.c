/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:34:53 by osancak           #+#    #+#             */
/*   Updated: 2025/09/01 15:33:58 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "core.h"

void	set_path(t_vars *vars)
{
	char	*path;

	free_split(vars->path);
	vars->path = NULL;
	path = get_env(vars->env, "PATH");
	if (path)
	{
		vars->path = ft_split(path, ':');
		free(path);
	}
}

char	*get_path(char **path, char *command)
{
	char	*ex_path;
	char	*____tmp;

	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
		else
			return (NULL);
	}
	while (path && *path)
	{
		____tmp = ft_strjoin(*path, "/", 0);
		ex_path = ft_strjoin(____tmp, command, 1);
		if (access(ex_path, X_OK) == 0)
			return (ex_path);
		free(ex_path);
		path++;
	}
	errno = 127;
	return (NULL);
}

void	free_split(char **split_data)
{
	int	i;

	if (!split_data)
		return ;
	i = -1;
	while (split_data[++i])
		free(split_data[i]);
	free(split_data);
}
