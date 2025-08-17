/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:34:53 by osancak           #+#    #+#             */
/*   Updated: 2025/08/17 09:42:58 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	set_path(t_vars *vars)
{
	char	*path;
	t_list	*env;

	env = vars->env;
	path = NULL;
	vars->path = NULL;
	while (env)
	{
		if (ft_strstr(env->data, "PATH=") && ft_strstr(env->data, "bin"))
		{
			path = env->data + 5;
			break ;
		}
		env = env->next;
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
			return (ft_strjoin("", command, 0));
		else
			*path = NULL;
	}
	while (*path)
	{
		____tmp = ft_strjoin(*path, "/", 0);
		ex_path = ft_strjoin(____tmp, command, 1);
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
