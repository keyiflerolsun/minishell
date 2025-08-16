/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:34:53 by osancak           #+#    #+#             */
/*   Updated: 2025/08/16 12:31:54 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	set_path(t_vars *vars)
{
	char	*path;
	t_list	*envs;

	envs = vars->envs;
	path = NULL;
	vars->path = NULL;
	while (envs)
	{
		if (ft_strstr(envs->data, "PATH=") && ft_strstr(envs->data, "bin"))
		{
			path = envs->data + 5;
			break ;
		}
		envs = envs->next;
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

void	free_split(char **split_data)
{
	int	i;

	i = -1;
	while (split_data[++i])
		free(split_data[i]);
	free(split_data);
}
