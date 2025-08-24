/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:23:12 by osancak           #+#    #+#             */
/*   Updated: 2025/08/24 11:56:59 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "core.h"

static void	get_input(int fd, char *limiter)
{
	char	*line;

	line = "";
	while (line)
	{
		line = readline(BOLD_YELLOW "heredot" BOLD_RED " > " RESET);
		if (ft_strstr(line, limiter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

pid_t	ft_heredot(t_vars *vars, char *limiter)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			error_exit("here_doc", 1);
		get_input(fd, limiter);
		close(fd);
		ft_clear(vars);
		exit(EXIT_SUCCESS);
	}
	if (pid < 0)
		error_exit("heredot", 1);
	return (pid);
}
