/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:02:35 by osancak           #+#    #+#             */
/*   Updated: 2025/08/08 16:26:50 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_path(t_pipe *vars, char **envp)
{
	char	*path;

	path = NULL;
	vars->path = NULL;
	while (*envp)
	{
		if (ft_strstr(*envp, "PATH=") && ft_strstr(*envp, "bin"))
		{
			path = *envp + 5;
			break ;
		}
		envp++;
	}
	if (path)
		vars->path = ft_split(path, ':');
}

char	*get_path(char **path, char *command)
{
	char	*ex_path;
	char	*____tmp;

	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
			return (ft_strjoin("", command));
		else
			*path = NULL;
	}
	while (*path)
	{
		____tmp = ft_strjoin(*path, "/");
		ex_path = ft_strjoin(____tmp, command);
		free(____tmp);
		if (access(ex_path, X_OK) == 0)
			return (ex_path);
		free(ex_path);
		path++;
	}
	errno = -42;
	return (NULL);
}

void	free_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}
